#include <convert_dream.hpp>
#include <chrono>
#include <thread>

convert_dream::convert_dream(fs::path &template_path, fs::path &dream_path) {
    player_count = savefile::read_player_count(dream_path);
    //cout << "player_count: "<< player_count << endl;

    fs::path dream_file_path = fs::path(dream_path / "dreamdownload.dat");

    ifstream dream_file;
    dream_file.open(dream_file_path, ios::in | ios::binary);

    savefile::check_players(dream_file, g_players);
    dream_file.close();
    template_check::template_check tc(template_path, g_players);

    template_check::result res = tc.check_template_files();

    //cout << "Template Error: " << (int)res.error_type << endl << res.additional_info << endl;

    if(res.error_type == template_check::error::none) {
        fs::path out_path = dream_path / "save";

        fs::remove_all(out_path);
        fs::create_directory(out_path);

        savefile::decrypt_batch(template_path, out_path, g_players);

        //cout << "decrypted!" << endl;

        copy_data(out_path, dream_file_path);


        u32 tick = static_cast<u32>(time(NULL));

        savefile::encrypt_batch(out_path, out_path, tick);

        cout << "encrypted! (done)" << endl;
    }
}

void convert_dream::copy_data(fs::path &out_path, fs::path &dream_file_path) {
    fs::path out_main_path(out_path / "main.dat");
    vector<fs::path> out_player_paths = savefile::get_player_folders(out_path, g_players);
    fstream main_file, player_file, dream_file;
    //cout << out_main_path.generic_string() << endl;

    u8 *land_main_buffer = new u8[REV_200_MAIN];
    u8 *player_buffer = new u8[REV_200_PERSONAL];
    u32 dream_size = mainSize + (playerSize * player_count);
    u8 *dream_buffer = new u8[dream_size];
    main_file.open(out_main_path, ios::in | ios::binary);
    dream_file.open(dream_file_path, ios::in | ios::binary);
    util::read_data((ifstream &)main_file, 0, land_main_buffer, REV_200_MAIN);
    util::read_data((ifstream &)dream_file, DreamHeaderSize, dream_buffer, dream_size);
    main_file.close();
    dream_file.close();
    
    get_account_table(land_main_buffer);
    util::write_data(land_main_buffer, SaveHeaderSize, dream_buffer, mainSize);
    fix_main(land_main_buffer);

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
        
        util::write_data(player_buffer, SaveHeaderSize, dream_buffer + mainSize + (playerSize * i), playerSize);
        u8 house_level = 0;
        util::read_data(land_main_buffer, SaveHeaderSize + houseLvlOffset +  (i * houseSize), &house_level, sizeof(u8));

        fix_player(player_buffer, dream_buffer + mainSize + (playerSize * i), house_level);

        player_file.open(out_player_personal_path, ios::out | ios::binary);
        util::write_data((ofstream &)player_file, 0, player_buffer, REV_200_PERSONAL);
        player_file.close();

        i++;
    }
}

void convert_dream::fix_main(void *main_buffer) {

    for(auto &fix : dream_land_event_flags) {
        u16 value = fix.second;
        util::write_data(main_buffer, SaveHeaderSize + EventFlagOffset + (fix.first * 2), &value, sizeof(u16));
    }

    //write AccountUID linkage (for Nintendo Switch Online)
    for (u8 player = 0; player < 8; player++) {
        if (g_players[player]) {
            util::write_data(main_buffer, SaveHeaderSize + GSavePlayerVillagerAccountOffset + (player * 0x48), &acc_table.accs[player], 0x10);
        }
    }
    //remove DreamInfo in dumped file
    u8 DreamInfoBuffer[DreamInfoSize] = { 0 };
    util::write_data(main_buffer, SaveHeaderSize + DreamIDOffset, DreamInfoBuffer, DreamInfoSize);
}

void convert_dream::fix_player(void *player_buffer, void *dream_player_buffer, u8 house_level) {
    //go through the event flags
    map<u16, u16> event_flags_map;
    for (auto const & event_flag : dream_player_event_flags) { 
        event_flags_map[event_flag] = 0; 
        util::read_data(dream_player_buffer, EventFlagsPlayerOffset + (event_flag * 2), &event_flags_map[event_flag], sizeof(u16));
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

    util::write_32(player_buffer, StorageSizeOffset, storage_size);
    util::write_32(player_buffer, Pocket1SizeOffset, pocket1_size);
    util::write_data(player_buffer, ExpandBaggageOffset, &expand_baggage, sizeof(u8));
    util::write_data(player_buffer, SaveHeaderSize + EventFlagsPlayerOffset + (672 * 2), &sell_pocket40, sizeof(u16));

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
    util::read_data(player_buffer, SaveHeaderSize + SpecialityFruitOffsetPersonal, &g_speciality_fruit, sizeof(u16));
    edit_recipe_bit(player_buffer, town_fruit_smoothies_map.find(g_speciality_fruit)->second, event_flags_map[1410]);

}

void convert_dream::edit_item_collect_bit(void *player_buffer, u16 collect_bit_offset, bool value){
    util::set_bit((char *)player_buffer + SaveHeaderSize + playerSize + ItemCollectBitOffset, collect_bit_offset, value);
}

void convert_dream::edit_recipe_bit(void *player_buffer, u16 collect_bit_offset, bool value){
    util::set_bit((char *)player_buffer + SaveHeaderSize + playerSize + RecipesOffset, collect_bit_offset, value);
}