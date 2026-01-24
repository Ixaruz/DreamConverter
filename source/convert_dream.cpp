#include "convert_dream.hpp"

#include "offsets_logic.hpp"
#include "template_check.hpp"

#include <util/util.hpp>
#include <savefile/savefile.hpp>
#include <save_structs/save_npc.hpp>
#include <save_structs/save_land_my_design.hpp>
#include <save_structs/save_land_time.hpp>
#include <save_structs/save_main_field.hpp>
#include <save_structs/save_npc_house_list.hpp>
#include <save_structs/save_player_house_list.hpp>
#include <save_structs/save_shop.hpp>
#include <chrono>
#include <cmath>

namespace { // annonymous
    void validate_arguments(fs::path &executable_path, fs::path &template_path, fs::path &dream_path) {
        if(!fs::exists(executable_path)) {
            throw std::runtime_error("executable path does not exist");
        }
        if(!fs::exists(template_path) || !fs::is_directory(template_path)) {
            throw std::runtime_error("template path does not exist or is not a directory");
        }
        if(!fs::exists(dream_path) || !fs::is_directory(dream_path)) {
            throw std::runtime_error("dream path does not exist or is not a directory");
        }
        if(!fs::exists(dream_path / "dream_land.dat")) {
            throw std::runtime_error("dream_land.dat does not exist in dream path");
        }
        if(!fs::exists(dream_path / "dream_land_meta.json")) {
            throw std::runtime_error("dream_land_meta.json does not exist in dream path");
        }
    }

    void check_players(ifstream &dream_file, u64 account_offset, bool *g_players) {
        for (u8 player = 0; player < 8; player++) {
            u64 offset = player * 0x48;
            u128 account_uid = 0;
            util::read_data(dream_file, dream_header_difference + account_offset + offset, &account_uid, 0x10);
            if (account_uid != 0) g_players[player] = true;
        }
    }

    vector<fs::path> get_player_folders(fs::path folder, bool *g_players) {
        vector<fs::path> player_folders;
        for (u8 player = 0; player < 8; player++) {
            if(g_players[player]) {
                player_folders.push_back(fs::path(folder / ("Villager" + to_string(player))));
            }
        }
        return player_folders;
    }
}

convert_dream::convert_dream(fs::path &executable_path, fs::path &template_path, fs::path &dream_path) {
    try
    {
        validate_arguments(executable_path, template_path, dream_path);
    }
    catch (std::runtime_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return;
    }
    player_count = savefile::read_player_count(dream_path);
    u32 revision = savefile::read_32_from_metadata(dream_path, "mAppReleaseVersion");
    dream_fhi = revision_checker::get_revision_info_by_save_revision(revision);

    u64 dream_offsets_index = Smmh::get_all_versions_index(dream_fhi);
    dream_yaml = Smmh::Land::AllVersions[dream_offsets_index];
    dream_player_yaml = Smmh::Player::AllVersions[dream_offsets_index];
    dream_player_other_yaml = Smmh::PlayerOther::AllVersions[dream_offsets_index];

    ifstream dream_file;
    fs::path dream_file_path = fs::path(dream_path / "dream_land.dat");
    dream_file.open(dream_file_path, ios::in | ios::binary);
    check_players(dream_file, dream_yaml.PlayerVillagerAccountTable.offset, g_players);
    dream_file.close();

    template_check::template_check tc(template_path, g_players);

    template_check::result res = tc.check_template_files();

    cout << "Template Error: " << (int)res.error_type << endl << res.additional_info << endl;

    main_fhi = tc.get_file_header_info();
    u64 main_offsets_index = Smmh::get_all_versions_index(main_fhi);
    main_yaml = Smmh::Land::AllVersions[main_offsets_index];
    player_yaml = Smmh::Player::AllVersions[main_offsets_index];
    player_other_yaml = Smmh::PlayerOther::AllVersions[main_offsets_index];

    if(res.error_type == template_check::error::none &&
       savefile::check_file_header_info_compatibility(tc.get_file_header_info(), revision_checker::get_revision_info_by_save_revision(revision)) != -1) {
        cout << "dream is compatible with template" << endl;
        fs::path out_path = dream_path / "save";

        fs::remove_all(out_path);
        fs::create_directory(out_path);

        savefile::decrypt_batch(template_path, out_path, g_players);

        cout << "decrypted!" << endl;

        copy_data_(out_path, dream_file_path);

        u32 tick = static_cast<u32>(time(NULL));

        savefile::encrypt_batch(out_path, out_path, tick, main_fhi.save_revision);

        cout << "encrypted! (done)" << endl;
    }
}

void convert_dream::copy_data_(fs::path &out_path, fs::path &dream_file_path) {

    fs::path main_file_path(out_path / "main.dat");
    fs::path landname_file_path(out_path / "landname.dat");
    vector<fs::path> out_player_paths = get_player_folders(out_path, g_players);
    uintmax_t main_file_size = fs::file_size(main_file_path);
    uintmax_t player_file_size = fs::file_size(out_player_paths[0] / "personal.dat");
    uintmax_t dream_file_size = fs::file_size(dream_file_path);
    u8 *main_buffer = new u8[main_file_size];
    u8 *player_buffer = new u8[player_file_size];
    u8 *dream_buffer = new u8[dream_file_size];
    fstream main_file, player_file, landname_file, dream_file;

    // MAIN
    main_file.open(main_file_path, ios::in | ios::binary);
    util::read_data((ifstream &)main_file, 0, main_buffer, main_file_size);
    main_file.close();

    dream_file.open(dream_file_path, ios::in | ios::binary);
    util::read_data((ifstream &)dream_file, 0, dream_buffer, dream_file_size);
    dream_file.close();

    // (landname)
    landname_file.open(landname_file_path, ios::out | ios::binary);
    write_landname_(dream_buffer, (ofstream &)landname_file);
    landname_file.close();

    for(const FieldLandInfo & field : main_fields_to_copy) {
        Smmh::OffsetSize const *dream_field_type = &(dream_yaml.*(field.member));
        Smmh::OffsetSize const *field_type = &(main_yaml.*(field.member));
        u64 dream_field_offset = dream_field_type->offset + dream_header_difference;
        u64 dream_field_size = dream_field_type->size;
        u64 field_offset = field_type->offset;
        u64 field_size = field_type->size;

        // skip fields that don't exist in both version (Hotel)
        if (dream_field_size == 0 || field_size == 0) {
            continue;
        }

        if(strcmp("NpcVillager", field.name) == 0)
        {
            auto npc = save_npc::get_save_npc(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            util::write_data(main_buffer, field_offset, const_cast<u8 *>(npc.get()->to_bin()), field_size);
        }
        else if(strcmp("LandTime", field.name) == 0)
        {
            auto time = save_land_time::get_save_land_time(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            util::write_data(main_buffer, field_offset, const_cast<u8 *>(time.get()->to_bin()), field_size);
        }
        else if(strcmp("LandMyDesign", field.name) == 0)
        {
            auto my_design = save_land_my_design::get_save_land_my_design(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            util::write_data(main_buffer, field_offset, const_cast<u8 *>(my_design.get()->to_bin()), field_size);
        }
        else if(strcmp("MainField", field.name) == 0)
        {
            auto main_field = save_main_field::get_save_main_field(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            util::write_data(main_buffer, field_offset, const_cast<u8 *>(main_field.get()->to_bin()), field_size);
        }
        else if(strcmp("PlayerHouseList", field.name) == 0)
        {
            auto player_house_list = save_player_house::get_save_player_house_list(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            for(int house_index = 0; house_index < (int)player_house_list.size(); house_index++) {
                u64 current_offset = field_offset + player_house_list[0].get()->get_size() * house_index;
                util::write_data(main_buffer + current_offset, 0, const_cast<u8 *>(player_house_list[house_index].get()->to_bin()), player_house_list[0].get()->get_size());
            }
        }
        else if(strcmp("NpcHouseList", field.name) == 0)
        {
            auto npc_house_list = save_npc_house::get_save_npc_house_list(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            for(int house_index = 0; house_index < (int)npc_house_list.size(); house_index++) {
                u64 current_offset = field_offset + npc_house_list[0].get()->get_size() * house_index;
                util::write_data(main_buffer + current_offset, 0, const_cast<u8 *>(npc_house_list[house_index].get()->to_bin()), npc_house_list[0].get()->get_size());
            }
        }
        else
        {
            u8 *nullbuffer = new u8[field_size]{0};
            // override with zeros first (in case the field we are writing is smaller than the input field)
            util::write_data(main_buffer, field_offset, nullbuffer, field_size);
            // write as much data as we can get from the dream_buffer (min value between the two struct sizes)
            util::write_data(main_buffer, field_offset, dream_buffer + dream_field_offset, min(field_size, dream_field_size));
            delete nullbuffer;
        }
    }
    fix_main_(main_buffer);
    main_file.open(main_file_path, ios::out | ios::binary);
    util::write_data((ofstream &)main_file, 0, main_buffer, main_file_size);
    main_file.close();

    // PLAYERS
    for(u8 i = 0; i < (u8)out_player_paths.size(); i++) {
        fs::path out_player_path = out_player_paths[i];
        fs::path out_player_personal_path = out_player_path / "personal.dat";
        //cout << out_player_personal_path.generic_string() << endl;
        player_file.open(out_player_personal_path, ios::in | ios::binary);
        util::read_data((ifstream &)player_file, 0, player_buffer, player_file_size);
        player_file.close();

        //preserve NetProfile and parts of ProfileMain (ReportInfo, LanguageCode and Ids)
        u8 *net_profile_buffer = new u8[player_yaml.NetProfile.size]{0};
        util::read_data(player_buffer, player_yaml.NetProfile.offset, net_profile_buffer, player_yaml.NetProfile.size);

        // this buffer holds everything after (including) PlayProfileReportInfo
        size_t size_of_profile_buffer = player_yaml.ProfileMain.size + player_yaml.ProfileMain.offset - player_yaml.PlayerProfileReportInfo.offset;
        u8 *profile_buffer = new u8[size_of_profile_buffer]{0};
        util::read_data(player_buffer, player_yaml.PlayerProfileReportInfo.offset, profile_buffer, size_of_profile_buffer);

        for(const FieldPlayerInfo & field : personal_fields_to_copy) {
            const Smmh::OffsetSize *dream_field_type = &(dream_player_yaml.*(field.member));
            const Smmh::OffsetSize *field_type = &(player_yaml.*(field.member));
            u64 dream_field_offset = dream_header_difference + dream_yaml.Land.size + (i * dream_player_yaml.Player.size) + dream_field_type->offset;
            u64 dream_field_size = dream_field_type->size;
            u64 field_offset = field_type->offset;
            u64 field_size = field_type->size;

            u8 *nullbuffer = new u8[field_size]{0};
            // override with zeros first (in case the field we are writing is smaller than the input field)
            util::write_data(player_buffer, field_offset, nullbuffer, field_size);
            // write as much data as we can get from the dream_buffer (min value between the two struct sizes)
            util::write_data(player_buffer, field_offset, dream_buffer + dream_field_offset, min(field_size, dream_field_size));
            delete nullbuffer;
        }
        u8 house_level = 0;
        util::read_data(main_buffer, main_yaml.PlayerHouseList.offset + (i * main_yaml.HouseList.size / 8), &house_level, sizeof(house_level));
        fix_player_(player_buffer, dream_buffer + dream_header_difference + dream_yaml.Land.size + (i * dream_player_yaml.Player.size), house_level, net_profile_buffer, profile_buffer);
        delete net_profile_buffer;
        delete profile_buffer;

        player_file.open(out_player_personal_path, ios::out | ios::binary);
        util::write_data((ofstream &)player_file, 0, player_buffer, player_file_size);
        player_file.close();
    }
    delete main_buffer;
    delete player_buffer;
    delete dream_buffer;
}

void convert_dream::write_landname_(void *dream_buffer, ofstream &landname_file) {
    // + IslandRubyType
    u64 town_name_size = dream_yaml.TownName.size + 2;
    u8 *town_name_buffer = new u8[town_name_size]{0};
    util::read_data(dream_buffer, dream_header_difference + dream_yaml.TownName.offset, town_name_buffer, town_name_size);
    util::write_data(landname_file, 0, town_name_buffer, town_name_size);
    delete town_name_buffer;
}

void convert_dream::fix_main_(void *main_buffer) {
    for(auto &fix : dream_land_event_flags) {
        util::write_data(main_buffer, main_yaml.EventFlag.offset + (fix.first * 2), const_cast<u16 *>(&fix.second), sizeof(u16));
    }

    // remove "net" (dream) profile from output file,
    // as we don't want the save file to be associated with the dream, that is (pressumably) still online
    u8 *net_land_profile_buffer = new u8[main_yaml.NetLandProfile.size]{0};
    util::write_data(main_buffer, main_yaml.NetLandProfile.offset, net_land_profile_buffer, main_yaml.NetLandProfile.size);
    delete net_land_profile_buffer;
}

void convert_dream::fix_player_(void *player_buffer, void *dream_player_buffer, u8 house_level, void const *net_profile_buffer, void const *profile_buffer) {
    //go through the event flags
    map<u16, u16> event_flags_map;
    for (auto const & event_flag : dream_player_event_flags) {
        event_flags_map[event_flag] = 0;
        util::read_data(dream_player_buffer, dream_player_yaml.EventFlag.offset + (event_flag * 2), &event_flags_map[event_flag], sizeof(u16));
        if(dream_player_event_flags_collect_item_map.find(event_flag) != dream_player_event_flags_collect_item_map.end()){
            edit_item_collect_bit_(player_buffer, dream_player_event_flags_collect_item_map.find(event_flag)->second, event_flags_map[event_flag]);
        }
    }
    //RcoStorageExpansion_v200_AddLevel
    u32 storage_size = storage_sizes[house_level + event_flags_map[1458]];
    //UpgradePocket30 and UpgradePocket40
    u32 pocket1_size = event_flags_map[669]? event_flags_map[670]? 0x14 : 0x0A : 0;
    u8 expand_baggage = event_flags_map[669]? event_flags_map[670]? 2 : 1 : 0;
    u16 sell_pocket40 = event_flags_map[669] ^ event_flags_map[670];

    util::write_32(player_buffer, player_other_yaml.StorageSize.offset, storage_size);
    util::write_32(player_buffer, player_other_yaml.Pocket1Size.offset, pocket1_size);
    util::write_data(player_buffer, player_other_yaml.ExpandBaggage.offset, &expand_baggage, sizeof(u8));
    util::write_data(player_buffer, save_header_size + player_yaml.EventFlag.offset + (672 * 2), &sell_pocket40, sizeof(u16));

    //Recipes
    for (u16 i : mainmenu_recipes) {
        edit_recipe_bit_(player_buffer, i, event_flags_map[171]);
    }
    for (u16 i : pretty_good_tools_recipes_recipes) {
        edit_recipe_bit_(player_buffer, i, event_flags_map[171]);
    }

    //vaulting pole
    if(event_flags_map[759] || event_flags_map[760]) {
        edit_recipe_bit_(player_buffer, 0x00B7, event_flags_map[171]);
    }

    for (u16 i : be_a_chef_recipes) {
        edit_recipe_bit_(player_buffer, i, event_flags_map[1410]);
    }

    // NetProfile and ProfileMain (parts)
    Smmh::OffsetSize const *net_player_profile = &player_yaml.NetProfile;
    Smmh::OffsetSize const *player_profile = &player_yaml.ProfileMain;
    Smmh::OffsetSize const *player_profile_report_info = &player_yaml.PlayerProfileReportInfo;
    util::write_data(player_buffer, net_player_profile->offset, net_profile_buffer, net_player_profile->size);
    util::write_data(player_buffer, player_profile_report_info->offset, profile_buffer, player_profile->size + player_profile->offset - player_profile_report_info->offset);

    u16 g_speciality_fruit = 0;
    util::read_data(player_buffer, player_yaml.SpecialityFruit.offset, &g_speciality_fruit, sizeof(u16));
    edit_recipe_bit_(player_buffer, town_fruit_smoothies_map.find(g_speciality_fruit)->second, event_flags_map[1410]);

}

void convert_dream::edit_item_collect_bit_(void *player_buffer, u16 collect_bit_offset, bool value) {
    util::set_bit((char *)player_buffer + player_other_yaml.ItemCollectBit.offset, collect_bit_offset, value);
}

void convert_dream::edit_recipe_bit_(void *player_buffer, u16 collect_bit_offset, bool value) {
    util::set_bit((char *)player_buffer + player_other_yaml.RecipeCollectBit.offset, collect_bit_offset, value);
}
