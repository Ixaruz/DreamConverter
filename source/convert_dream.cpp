#include <convert_dream.hpp>

ACNHByaml *get_byaml(fs::path smmh_path, revision_checker::file_header_info fhi) {
    fs::path smmh_byaml_file_path(smmh_path / smmh_paths_by_revision::game(fhi));
    ifstream byaml_file;

    byaml_file.open(smmh_byaml_file_path, ios::in | ios::binary);
    u8 *byaml_buffer = new u8[fs::file_size(smmh_byaml_file_path)];
    util::read_data(byaml_file, 0, byaml_buffer, fs::file_size(smmh_byaml_file_path));
    byaml_file.close();

    return new ACNHByaml(byaml_buffer, fs::file_size(smmh_byaml_file_path));
}

void convert_dream::setup_(fs::path &executable_path) {
    main_yaml = get_byaml(executable_path.remove_filename(), main_fhi);
    main_size =                         main_yaml->GetSize(main_field_type,
                                                           vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Land")}));
    dream_main_size =                   dream_yaml->GetSize(main_field_type,
                                                            vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Land")}));
    player_size =                       main_yaml->GetSize(personal_field_type,
                                                           vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Player")}));
    dream_player_size =                 dream_yaml->GetSize(personal_field_type,
                                                            vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Player")}));
    event_flag_land_offset =            main_yaml->CalcOffsets(main_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Land"),
                                                                    MurmurHash3::Calc_CEval("EventFlag")}));
    dream_event_flag_land_offset =      dream_yaml->CalcOffsets(main_field_type,
                                                                vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Land"),
                                                                    MurmurHash3::Calc_CEval("EventFlag")}));
    event_flag_player_offset =          main_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Player"),
                                                                    MurmurHash3::Calc_CEval("EventFlag")}));
    dream_event_flag_player_offset =    dream_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Player"),
                                                                    MurmurHash3::Calc_CEval("EventFlag")}));
    speciality_fruit_offset =           main_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Player"),
                                                                    MurmurHash3::Calc_CEval("ProfileMain"),
                                                                    MurmurHash3::Calc_CEval("SpecialityFruit")}));
    dream_speciality_fruit_offset =     dream_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Player"),
                                                                    MurmurHash3::Calc_CEval("ProfileMain"),
                                                                    MurmurHash3::Calc_CEval("SpecialityFruit")}));
    item_collect_bit_offset =           main_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("PlayerOther"),
                                                                    MurmurHash3::Calc_CEval("ItemCollectBit")}));
    recipe_collect_bit_offset =         main_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("PlayerOther"),
                                                                    MurmurHash3::Calc_CEval("CraftingRecipeCollect"),
                                                                    MurmurHash3::Calc_CEval("RecipeCollectBit")}));
    storage_size_offset =               main_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("PlayerOther"),
                                                                    MurmurHash3::Calc_CEval("ItemChest"),
                                                                    MurmurHash3::Calc_CEval("ItemHolder"),
                                                                    1281327397 /*_4c5f8125*/}));
    pocket_1_size_offset =              main_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("PlayerOther"),
                                                                    MurmurHash3::Calc_CEval("ItemBaggage"),
                                                                    MurmurHash3::Calc_CEval("ItemBag"),
                                                                    MurmurHash3::Calc_CEval("ItemHolder"),
                                                                    1281327397 /*_4c5f8125*/}));
    expand_baggage_offset =             main_yaml->CalcOffsets(personal_field_type,
                                                               vector<u32>({
                                                                    MurmurHash3::Calc_CEval("PlayerOther"),
                                                                    MurmurHash3::Calc_CEval("ItemBaggage"),
                                                                    MurmurHash3::Calc_CEval("ExpandBaggage")}));
}

convert_dream::convert_dream(fs::path &executable_path, fs::path &template_path, fs::path &dream_path) {
    player_count = savefile::read_player_count(dream_path);
    u32 revision = savefile::read_32_from_metadata(dream_path, "mAppReleaseVersion");
    dream_fhi = revision_checker::get_revision_info_by_save_revision(revision);
    dream_yaml = get_byaml(executable_path.remove_filename(), dream_fhi);
    u32 dream_account_table_offset =    dream_yaml->CalcOffsets(main_field_type,
                                                                vector<u32>({
                                                                    MurmurHash3::Calc_CEval("Land"),
                                                                    MurmurHash3::Calc_CEval("PlayerVillagerAccountTable")}));

    ifstream dream_file;
    fs::path dream_file_path = fs::path(dream_path / "dream_land.dat");
    dream_file.open(dream_file_path, ios::in | ios::binary);
    savefile::check_players(dream_file, dream_account_table_offset, g_players);
    dream_file.close();

    template_check::template_check tc(template_path, g_players);

    template_check::result res = tc.check_template_files();

    cout << "Template Error: " << (int)res.error_type << endl << res.additional_info << endl;

    main_fhi = tc.get_file_header_info();
    // setup variables and shit
    this->setup_(executable_path);

    if(res.error_type == template_check::error::none &&
       savefile::check_file_header_info_compatibility(tc.get_file_header_info(), revision_checker::get_revision_info_by_save_revision(revision)) != -1) {
        cout << "dream is compatible with template" << endl;
        fs::path out_path = dream_path / "save";

        fs::remove_all(out_path);
        fs::create_directory(out_path);

        savefile::decrypt_batch(template_path, out_path, g_players);

        cout << "decrypted!" << endl;

        copy_data(out_path, dream_file_path);

        fs::path enc_out_path = dream_path / "enc";
        fs::remove_all(enc_out_path);
        fs::create_directory(enc_out_path);

        u32 tick = static_cast<u32>(time(NULL));

        savefile::encrypt_batch(out_path, enc_out_path, tick);

        cout << "encrypted! (done)" << endl;
    }
}

void convert_dream::copy_data(fs::path &out_path, fs::path &dream_file_path) {

    fs::path main_file_path(out_path / "main.dat");
    vector<fs::path> out_player_paths = savefile::get_player_folders(out_path, g_players);
    u32 main_file_size = fs::file_size(main_file_path);
    u32 player_file_size = fs::file_size(out_player_paths[0] / "personal.dat");
    u32 dream_file_size = fs::file_size(dream_file_path);
    u8 *main_buffer = new u8[main_file_size];
    u8 *player_buffer = new u8[player_file_size];
    u8 *dream_buffer = new u8[dream_file_size];
    fstream main_file, player_file, dream_file;

    // MAIN=
    main_file.open(main_file_path, ios::in | ios::binary);
    util::read_data((ifstream &)main_file, 0, main_buffer, main_file_size);
    main_file.close();

    dream_file.open(dream_file_path, ios::in | ios::binary);
    util::read_data((ifstream &)dream_file, 0, dream_buffer, dream_file_size);
    dream_file.close();

    for(vector<u32> field : main_fields_to_copy) {
        printf("field: 0x%08X %u\n", field.back(), field.back());
        u64 field_offset = main_yaml->CalcOffsets(main_field_type, field);
        u64 field_size = main_yaml->GetSize(main_field_type, field);
        printf("field offset: 0x%lX field size: 0x%lX\n", field_offset, field_size);
        u64 dream_field_offset = dream_yaml->CalcOffsets(main_field_type, field) + dream_header_difference;
        u64 dream_field_size = dream_yaml->GetSize(main_field_type, field);
        printf("dream field offset: 0x%lX dream field size: 0x%lX\n------------------------\n", dream_field_offset, dream_field_size);

        switch (field.back())
        {
        case MurmurHash3::Calc_CEval("NpcVillager"):
        {
            auto npc = save_npc::get_save_npc(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            util::write_data(main_buffer + field_offset, 0, const_cast<u8 *>(npc.get()->to_bin()), field_size);
            break;
        }
        case MurmurHash3::Calc_CEval("LandTime"):
        {
            auto time = save_land_time::get_save_land_time(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            util::write_data(main_buffer + field_offset, 0, const_cast<u8 *>(time.get()->to_bin()), field_size);
            break;
        }
        case MurmurHash3::Calc_CEval("LandMyDesign"):
        {
            auto my_design = save_land_my_design::get_save_land_my_design(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            util::write_data(main_buffer + field_offset, 0, const_cast<u8 *>(my_design.get()->to_bin()), field_size);
            break;
        }
        case MurmurHash3::Calc_CEval("MainField"):
        {
            auto main_field = save_main_field::get_save_main_field(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            util::write_data(main_buffer + field_offset, 0, const_cast<u8 *>(main_field.get()->to_bin()), field_size);
            break;
        }
        case MurmurHash3::Calc_CEval("PlayerHouseList"):
        {
            auto player_house_list = save_player_house::get_save_player_house_list(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            for(int house_index = 0; house_index < (int)player_house_list.size(); house_index++) {
                util::write_data(main_buffer + field_offset, 0, const_cast<u8 *>(player_house_list[house_index].get()->to_bin()), player_house_list[0].get()->get_size());
            }
            break;
        }
        case MurmurHash3::Calc_CEval("NpcHouseList"):
        {
            auto npc_house_list = save_npc_house::get_save_npc_house_list(dream_buffer + dream_field_offset, dream_fhi.save_revision, main_fhi.save_revision);
            for(int house_index = 0; house_index < (int)npc_house_list.size(); house_index++) {
                util::write_data(main_buffer + field_offset, 0, const_cast<u8 *>(npc_house_list[house_index].get()->to_bin()), npc_house_list[0].get()->get_size());
            }
            break;
        }
        default:
        {
            u8 *nullbuffer = new u8[field_size]{0};
            // override with zeros first (in case the field we are writing is smaller than the input field)
            util::write_data(main_buffer + field_offset, 0, nullbuffer, field_size);
            // write as much data as we can get from the dream_buffer (min value between the two struct sizes)
            util::write_data(main_buffer + field_offset, 0, dream_buffer + dream_field_offset, min(field_size, dream_field_size));
            delete nullbuffer;
            break;
        }
        }
    }
    fix_main(main_buffer);
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

        for(vector<u32> field : personal_fields_to_copy) {
            printf("field: 0x%08X %u\n", field.back(), field.back());
            u64 field_offset = main_yaml->CalcOffsets(personal_field_type, field);
            u64 field_size = main_yaml->GetSize(personal_field_type, field);
            printf("field offset: 0x%lX field size: 0x%lX\n", field_offset, field_size);
            u64 dream_field_offset = dream_yaml->CalcOffsets(personal_field_type, field) + dream_header_difference + dream_main_size + (i * dream_player_size);
            u64 dream_field_size = dream_yaml->GetSize(personal_field_type, field);
            printf("dream field offset: 0x%lX dream field size: 0x%lX\n------------------------\n", dream_field_offset, dream_field_size);

            u8 *nullbuffer = new u8[field_size]{0};
            // override with zeros first (in case the field we are writing is smaller than the input field)
            util::write_data(player_buffer + field_offset, 0, nullbuffer, field_size);
            // write as much data as we can get from the dream_buffer (min value between the two struct sizes)
            util::write_data(player_buffer + field_offset, 0, dream_buffer + dream_field_offset, min(field_size, dream_field_size));
            delete nullbuffer;
        }
        u8 house_level = 0;
        u32 house_lvl_offset =  main_yaml->CalcOffsets(main_field_type,
                                                       vector<u32>({
                                                            MurmurHash3::Calc_CEval("Land"),
                                                            MurmurHash3::Calc_CEval("PlayerHouseList")}));
        u32 house_size =        main_yaml->GetSize(main_field_type,
                                                   vector<u32>({
                                                            MurmurHash3::Calc_CEval("Land"),
                                                            MurmurHash3::Calc_CEval("PlayerHouseList"),
                                                            MurmurHash3::Calc_CEval("HouseList")})); // this only gives us the size of ONE element so its fine
        util::read_data(main_buffer, house_lvl_offset +  (i * house_size), &house_level, sizeof(house_level));
        fix_player(player_buffer, dream_buffer + dream_header_difference + dream_main_size + (i * dream_player_size), house_level);

        player_file.open(out_player_personal_path, ios::out | ios::binary);
        util::write_data((ofstream &)player_file, 0, player_buffer, player_file_size);
        player_file.close();
    }
}

/*
void convert_dream::copy_data(fs::path &out_path, fs::path &dream_file_path) {
    fs::path out_main_path(out_path / "main.dat");
    vector<fs::path> out_player_paths = savefile::get_player_folders(out_path, g_players);
    fstream main_file, player_file, dream_file;
    //cout << out_main_path.generic_string() << endl;

    u8 *land_main_buffer = new u8[REV_200_MAIN];
    u8 *player_buffer = new u8[REV_200_PERSONAL];
    u32 dream_field_size = mainSize + (playerSize * player_count);
    u8 *dream_buffer = new u8[dream_field_size];
    main_file.open(out_main_path, ios::in | ios::binary);
    dream_file.open(dream_file_path, ios::in | ios::binary);
    util::read_data((ifstream &)main_file, 0, land_main_buffer, REV_200_MAIN);
    util::read_data((ifstream &)dream_file, dream_header_size, dream_buffer, dream_field_size);
    main_file.close();
    dream_file.close();

    get_account_table(land_main_buffer);
    util::write_data(land_main_buffer, save_header_size, dream_buffer, mainSize);
    //fix_main(land_main_buffer);

    main_file.open(out_main_path, ios::out | ios::binary);
    util::write_data((ofstream &)main_file, 0, land_main_buffer, REV_200_MAIN);
    main_file.close();

    u8 i = 0;
    for(fs::path &out_player_path : out_player_paths) {
        fs::path out_player_personal_path = out_player_path / "personal.dat";
        //cout << out_player_personal_path.generic_string() << endl;
        player_file.open(out_player_personal_path, ios::in | ios::binary);
        util::read_data((ifstream &)player_file, 0, player_buffer, REV_200_PERSONAL);
        player_file.close();

        util::write_data(player_buffer, save_header_size, dream_buffer + mainSize + (playerSize * i), playerSize);
        u8 house_level = 0;
        util::read_data(land_main_buffer, save_header_size + houseLvlOffset +  (i * houseSize), &house_level, sizeof(u8));

        //fix_player(player_buffer, dream_buffer + mainSize + (playerSize * i), house_level);

        player_file.open(out_player_personal_path, ios::out | ios::binary);
        util::write_data((ofstream &)player_file, 0, player_buffer, REV_200_PERSONAL);
        player_file.close();

        i++;
    }
}
*/

void convert_dream::fix_main(void *main_buffer) {
    for(auto &fix : dream_land_event_flags) {
        util::write_data(main_buffer, event_flag_land_offset + (fix.first * 2), const_cast<u16 *>(&fix.second), sizeof(u16));
    }
}

void convert_dream::fix_player(void *player_buffer, void *dream_player_buffer, u8 house_level) {
    //go through the event flags
    map<u16, u16> event_flags_map;
    for (auto const & event_flag : dream_player_event_flags) {
        event_flags_map[event_flag] = 0;
        util::read_data(dream_player_buffer, dream_event_flag_player_offset + (event_flag * 2), &event_flags_map[event_flag], sizeof(u16));
        if(dream_player_event_flags_collect_item_map.find(event_flag) != dream_player_event_flags_collect_item_map.end()){
            edit_item_collect_bit(player_buffer, dream_player_event_flags_collect_item_map.find(event_flag)->second, event_flags_map[event_flag]);
        }
    }
    //RcoStorageExpansion_v200_AddLevel
    u32 storage_size = storage_sizes[house_level + event_flags_map[1458]];
    //UpgradePocket30 and UpgradePocket40
    u32 pocket1_size = event_flags_map[669]? event_flags_map[670]? 0x14 : 0x0A : 0;
    u8 expand_baggage = event_flags_map[669]? event_flags_map[670]? 2 : 1 : 0;
    bool sell_pocket40 = event_flags_map[669] ^ event_flags_map[670];

    util::write_32(player_buffer, storage_size_offset, storage_size);
    util::write_32(player_buffer, pocket_1_size_offset, pocket1_size);
    util::write_data(player_buffer, expand_baggage_offset, &expand_baggage, sizeof(u8));
    util::write_data(player_buffer, save_header_size + event_flag_player_offset + (672 * 2), &sell_pocket40, sizeof(u16));

    //Recipes
    for (u16 i : mainmenu_recipes) {
        edit_recipe_bit(player_buffer, i, event_flags_map[171]);
    }
    for (u16 i : pretty_good_tools_recipes_recipes) {
        edit_recipe_bit(player_buffer, i, event_flags_map[171]);
    }

    //vaulting pole
    if(event_flags_map[759] || event_flags_map[760]) {
        edit_recipe_bit(player_buffer, 0x00B7, event_flags_map[171]);
    }

    for (u16 i : be_a_chef_recipes) {
        edit_recipe_bit(player_buffer, i, event_flags_map[1410]);
    }
    u16 g_speciality_fruit = 0;
    util::read_data(player_buffer, speciality_fruit_offset, &g_speciality_fruit, sizeof(u16));
    edit_recipe_bit(player_buffer, town_fruit_smoothies_map.find(g_speciality_fruit)->second, event_flags_map[1410]);

}

void convert_dream::edit_item_collect_bit(void *player_buffer, u16 collect_bit_offset, bool value){
    util::set_bit((char *)player_buffer + item_collect_bit_offset, collect_bit_offset, value);
}

void convert_dream::edit_recipe_bit(void *player_buffer, u16 collect_bit_offset, bool value){
    util::set_bit((char *)player_buffer + recipe_collect_bit_offset, collect_bit_offset, value);
}
