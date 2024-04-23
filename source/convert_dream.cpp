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

convert_dream::convert_dream(fs::path &executable_path, fs::path &template_path, fs::path &dream_path) {
    player_count = savefile::read_player_count(dream_path);
    u32 revision = savefile::read_32_from_metadata(dream_path, "mAppReleaseVersion");

    fs::path dream_file_path = fs::path(dream_path / "dream_land.dat");
    ifstream dream_file;
    dream_file.open(dream_file_path, ios::in | ios::binary);
    savefile::check_players(dream_file, g_players);
    u8 *main_dream_buffer = new u8[fs::file_size(dream_file_path)];
    util::read_data(dream_file, 0, main_dream_buffer, fs::file_size(dream_file_path));
    dream_file.close();
    template_check::template_check tc(template_path, g_players);

    template_check::result res = tc.check_template_files();

    cout << "Template Error: " << (int)res.error_type << endl << res.additional_info << endl;

    main_fhi = tc.get_file_header_info();
    dream_fhi = *(revision_checker::get_revision_info_by_save_revision(revision));
    main_yaml = get_byaml(executable_path.remove_filename(), main_fhi);
    dream_yaml = get_byaml(executable_path.remove_filename(), dream_fhi);

    
    //u32 fieldType = MurmurHash3::Calc_CEval("::Game::SaveMain");
    // std::vector<u32> fieldNames1 {
    //     MurmurHash3::Calc_CEval("Land")
    // };
    // std::vector<u32> fieldNames2 {
    //     MurmurHash3::Calc_CEval("Land"),
    //     MurmurHash3::Calc_CEval("NpcHouseList")
    // };

    // u64 offset = mainyaml->CalcOffsets(fieldType, fieldNames2) - mainyaml->CalcOffsets(fieldType, fieldNames1);
    // printf("Offset: %llu (0x%llX)\n", offset, offset);
    // u64 size = mainyaml->GetSize(fieldType, fieldNames2);
    // printf("size: %llu (0x%llX)\n", size, size);

    //offset = maindreamyaml->CalcOffsets(fieldType, fieldNames2) - maindreamyaml->CalcOffsets(fieldType, fieldNames1);
    // printf("Offset: %llu (0x%llX)\n", offset, offset);
    // size = maindreamyaml->GetSize(fieldType, fieldNames2);
    // printf("size: %llu (0x%llX)\n", size, size);

    // vector<vector<u64>> field_sizes_by_revision(main_fields_to_copy.size(), vector<u64>(revision_checker::revision_info.size(), 0));
    // int j = 0;
    // for(auto revsion : revision_checker::revision_info){
    //     string revision_smmh_path = smmh_paths_by_revision::game(*revsion);
    //     fs::path revision_main_yaml_path(executable_path.remove_filename() / revision_smmh_path);
    //     cout << revision_main_yaml_path.generic_string() << endl;
    //     ifstream revision_main_yaml_file;
        
    //     revision_main_yaml_file.open(revision_main_yaml_path, ios::in | ios::binary);
    //     size_t file_size = fs::file_size(revision_main_yaml_path);
    //     u8 *revision_main_yaml_buffer = new u8[file_size];
    //     util::read_data(revision_main_yaml_file, 0, revision_main_yaml_buffer, file_size);
    //     revision_main_yaml_file.close();

    //     ACNHByaml *revision_mainyaml = new ACNHByaml(revision_main_yaml_buffer, file_size);
    //     int i = 0;
    //     for(vector<u32> field : main_fields_to_copy) {
    //         //printf("field: 0x%08X\n", field.back());
    //         u64 offset = revision_mainyaml->CalcOffsets(fieldType, field);
    //         u64 size = revision_mainyaml->GetSize(fieldType, field);
    //         field_sizes_by_revision.at(i).at(j) = size;
    //         //printf("Offset: 0x%llX size: 0x%llX\n------------------------\n", offset, size);
    //         i++;
    //     }
    //     delete revision_main_yaml_buffer, revision_mainyaml;
    //     j++;
    // }

    // int i = 0;
    // for(vector<u64> field : field_sizes_by_revision){
    //     //printf("field %d\n", i);
    //     for(auto elem : field) printf("%llX ", elem);
    //     printf("\n");
    //     auto it = std::adjacent_find( field.begin(), field.end(), std::not_equal_to<>());
    //     if ( it != field.end() )
    //     {
    //         printf("field  0x%08X had size change\n", main_fields_to_copy[i].back());
    //         //printf("begin was %llX, but now is %llX\n", *field.begin(), *it);
    //     }
    //     i++;
    // }

    // printf("\n\n\n\n\n");

    // fieldType = MurmurHash3::Calc_CEval("::Game::SavePlayer");

    // vector<vector<u64>> personal_field_sizes_by_revision(personal_fields_to_copy.size(), vector<u64>(revision_checker::revision_info.size(), 0));
    // j = 0;
    // for(auto revsion : revision_checker::revision_info){
    //     string revision_smmh_path = smmh_paths_by_revision::game(*revsion);
    //     fs::path revision_main_yaml_path(executable_path.remove_filename() / revision_smmh_path);
    //     cout << revision_main_yaml_path.generic_string() << endl;
    //     ifstream revision_main_yaml_file;
        
    //     revision_main_yaml_file.open(revision_main_yaml_path, ios::in | ios::binary);
    //     size_t file_size = fs::file_size(revision_main_yaml_path);
    //     u8 *revision_main_yaml_buffer = new u8[file_size];
    //     util::read_data(revision_main_yaml_file, 0, revision_main_yaml_buffer, file_size);
    //     revision_main_yaml_file.close();

    //     ACNHByaml *revision_mainyaml = new ACNHByaml(revision_main_yaml_buffer, file_size);
    //     int i = 0;
    //     for(vector<u32> field : personal_fields_to_copy) {
    //         //printf("field: 0x%08X\n", field.back());
    //         u64 offset = revision_mainyaml->CalcOffsets(fieldType, field);
    //         u64 size = revision_mainyaml->GetSize(fieldType, field);
    //         personal_field_sizes_by_revision.at(i).at(j) = size;
    //         //printf("Offset: 0x%llX size: 0x%llX\n------------------------\n", offset, size);
    //         i++;
    //     }
    //     delete revision_main_yaml_buffer, revision_mainyaml;
    //     j++;
    // }

    // i = 0;
    // for(vector<u64> field : personal_field_sizes_by_revision){
    //     //printf("field %d\n", i);
    //     for(auto elem : field) printf("%llX ", elem);
    //     printf("\n");
    //     auto it = std::adjacent_find( field.begin(), field.end(), std::not_equal_to<>());
    //     if ( it != field.end() )
    //     {
    //         printf("field  0x%08X had size change\n", personal_fields_to_copy[i].back());
    //         //printf("begin was %llX, but now is %llX\n", *field.begin(), *it);
    //     }
    //     i++;
    // }


    // for(vector<u32> field : main_fields_to_copy) {
    //     printf("field: 0x%08X\n", field.back());
    //     u64 offset = maindreamyaml->CalcOffsets(fieldType, field);
    //     u64 size = maindreamyaml->GetSize(fieldType, field);
    //     printf("Offset: 0x%llX size: 0x%llX\n", offset, size);
    //     offset = mainyaml->CalcOffsets(fieldType, field);
    //     size = mainyaml->GetSize(fieldType, field);
    //     printf("Offset: 0x%llX size: 0x%llX\n------------------------\n", offset, size);

    // }

    // ByamlNode NpcHouseList = mainyaml->GetNode(fieldType, fieldNames2);

    // for (auto elem2 : (*NpcHouseList.hash)) {
    //     if (strcmp(elem2.first, "b4a58247") == 0 && elem2.second.type == NodeType::Int64) { //b4a58247 == "Size"
    //         printf("\"%s\" : 0x%016llx\n", elem2.first, elem2.second.Int64);
    //     }
    // }
    
    // fieldType = MurmurHash3::Calc_CEval("::Game::SaveMain");

    // std::vector<u32> fieldNames2 {
    //     MurmurHash3::Calc_CEval("Land"),
    //     MurmurHash3::Calc_CEval("PlayerHouseList")
    // };
    // save_player_house::save_player_house_type type;

    // u64 offset = maindreamyaml->CalcOffsets(fieldType, fieldNames2) + dream_header_difference;
    // printf("Offset: %llu (0x%llX)\n", offset, offset);
    // std::unique_ptr<save_player_house::save_player_house_1> house = save_player_house::get_save_player_house(main_dream_buffer + offset, (u16)revision, (u16)tc.get_file_header_info().save_revision, type);
    // cout << "revision: " << revision << endl;
    // switch(type) {
    //     case save_player_house::save_player_house_type::type_1:
    //         cout << "type_1" << endl;
    //         break;
    //     case save_player_house::save_player_house_type::type_2:
    //         cout << "type_2" << endl;
    //         break;
    // }

    // fs::path out_path = dream_path / "save";
    // savefile::decrypt_batch(template_path, out_path, {g_players});
    // u8 *land_main_buffer = new u8[REV_200_MAIN];
    // fs::path out_main_path(out_path / "main.dat");
    // fstream main_file;
    // main_file.open(out_main_path, ios::in | ios::binary);
    // util::read_data((ifstream &)main_file, 0, land_main_buffer, REV_200_MAIN);
    // main_file.close();
    // u64 offset = main_yaml->CalcOffsets(main_field_type, fieldNames2);
    // printf("Offset: %llu (0x%llX)\n", offset, offset);
    // auto house = save_player_house::get_save_player_house(land_main_buffer + offset, (u16)tc.get_file_header_info().save_revision, 22, type);
    // cout << "revision: " << tc.get_file_header_info().save_revision << endl;
    // u8 * player_house = nullptr;
    // int house_size = 0;
    // string extension = "";
    // switch(type) {
    //     case save_player_house::save_player_house_type::type_1:
    //         cout << "type_1" << endl;
    //         player_house = (*house.get())->get_everything();
    //         house_size = save_player_house::save_player_house_1::get_size();
    //         extension = "nhph";
    //         break;
    //     case save_player_house::save_player_house_type::type_2:
    //         player_house = ((save_player_house::save_player_house_2 *)(*house.get()))->get_everything();
    //         house_size = save_player_house::save_player_house_2::get_size();
    //         extension = "nhph2";
    //         cout << "type_2" << endl;
    //         break;
    // }

    // fs::path out_house_0_path(out_path / "house0");
    // out_house_0_path.replace_extension(extension);
    // fstream out_house_0_file;
    // out_house_0_file.open(out_house_0_path, ios::out | ios::binary);
    // util::write_data((ofstream &)out_house_0_file, 0, player_house, house_size);
    // out_house_0_file.close();
    

    std::vector<u32>  fieldNames2 {
        MurmurHash3::Calc_CEval("Land"), 
        MurmurHash3::Calc_CEval("Npc"), 
        MurmurHash3::Calc_CEval("NpcVillager")
    };
    save_npc::save_npc_type type;

    fs::path out_path = dream_path / "save";
    fs::remove_all(out_path);
    fs::create_directory(out_path);
    cout << "foo" << endl;
    savefile::decrypt_batch(template_path, out_path, {g_players});
    u8 *land_main_buffer = new u8[REV_200_MAIN];
    fs::path out_main_path(out_path / "main.dat");
    fstream main_file;
    main_file.open(out_main_path, ios::in | ios::binary);
    util::read_data((ifstream &)main_file, 0, land_main_buffer, REV_200_MAIN);
    main_file.close();
    u64 offset = main_yaml->CalcOffsets(main_field_type, fieldNames2);
    printf("Offset: %llu (0x%llX)\n", offset, offset);
    auto npc = save_npc::get_save_npc(land_main_buffer + offset, main_fhi.save_revision, 11, type);
    cout << "template uses revision: " << main_fhi.save_revision << endl;
    u8 * npc_buffer = nullptr;
    int npc_size = 0;
    string extension = "dat";
    npc_size = npc.get()->get_size();
    npc_buffer = new u8[npc_size]{0};
    memcpy(npc_buffer, npc.get()->get_everything(), npc_size);
    switch(type) {
        case save_npc::save_npc_type::type_1:
            cout << "type_1" << endl;
            break;
        case save_npc::save_npc_type::type_2:
            cout << "type_2" << endl;
            break;
        case save_npc::save_npc_type::type_3:
            cout << "type_3" << endl;
            break;
        default:
            cout << "noffing" << endl;
    }
    fs::path out_npc_path(out_path / "npc");
    out_npc_path.replace_extension(extension);
    fstream out_npc_file;
    out_npc_file.open(out_npc_path, ios::out | ios::binary);
    util::write_data((ofstream &)out_npc_file, 0, npc_buffer, npc_size);
    out_npc_file.close();

    /*
    if(res.error_type == template_check::error::none && savefile::check_file_header_info_compatibility(tc.get_file_header_info(), *revision_checker::revision_info[revision]) != -1) {
        cout << "dream is compatible with template" << endl;
        fs::path out_path = dream_path / "save";

        fs::remove_all(out_path);
        fs::create_directory(out_path);

        savefile::decrypt_batch(template_path, out_path, g_players);

        cout << "decrypted!" << endl;

        std::vector<u32> fieldNames2 {
            MurmurHash3::Calc_CEval("Land"),
            MurmurHash3::Calc_CEval("PlayerHouseList")
        };
        //save_player_house::save_player_house_type type;

        // u64 offset = maindreamyaml->CalcOffsets(fieldType, fieldNames2) + dream_header_difference;
        // printf("Offset: %llu (0x%llX)\n", offset, offset);
        // std::unique_ptr<save_player_house::save_player_house_1> house = save_player_house::get_save_player_house(main_dream_buffer + offset, (u16)revision, (u16)tc.get_file_header_info().save_revision, type);
        // cout << "revision: " << revision << endl;
        // switch(type) {
        //     case save_player_house::save_player_house_type::type_1:
        //         cout << "type_1" << endl;
        //         break;
        //     case save_player_house::save_player_house_type::type_2:
        //         cout << "type_2" << endl;
        //         break;
        // }

        u8 *land_main_buffer = new u8[REV_200_MAIN];
        fs::path out_main_path(out_path / "main.dat");
        fstream main_file;
        main_file.open(out_main_path, ios::in | ios::binary);
        util::read_data((ifstream &)main_file, 0, land_main_buffer, REV_200_MAIN);
        main_file.close();
        u64 offset = main_yaml->CalcOffsets(main_field_type, fieldNames2);
        printf("Offset: %llu (0x%llX)\n", offset, offset);

        copy_data(out_path, dream_file_path);


        //u32 tick = static_cast<u32>(time(NULL));

        //savefile::encrypt_batch(out_path, out_path, tick);

        //cout << "encrypted! (done)" << endl;
    }
    */
}

void convert_dream::copy_data(fs::path &out_path, fs::path &dream_file_path) {
        
    fs::path main_file_path(out_path / "main.dat");
    u32 main_file_size = fs::file_size(main_file_path);
    u32 dream_file_size = fs::file_size(dream_file_path);
    u8 *main_buffer = new u8[main_file_size];
    u8 *dream_buffer = new u8[dream_file_size];


    fstream main_file, dream_file;
    
    main_file.open(main_file_path, ios::in | ios::binary);
    util::read_data((ifstream &)main_file, 0, main_buffer, main_file_size);
    main_file.close();

    dream_file.open(dream_file_path, ios::in | ios::binary);
    util::read_data((ifstream &)dream_file, 0, dream_buffer, dream_file_size);
    dream_file.close();

    for(vector<u32> field : main_fields_to_copy) {
        printf("field: 0x%08X\n", field.back());
        u64 main_offset = main_yaml->CalcOffsets(main_field_type, field);
        u64 main_size = main_yaml->GetSize(main_field_type, field);
        printf("main offset: 0x%llX main size: 0x%llX\n", main_offset, main_size);
        u64 dream_offset = dream_yaml->CalcOffsets(main_field_type, field) + dream_header_difference;
        u64 dream_size = dream_yaml->GetSize(main_field_type, field);
        printf("dream offset: 0x%llX dream size: 0x%llX\n------------------------\n", dream_offset, dream_size);

        switch (field.back())
        {
        case MurmurHash3::Calc_CEval("NpcVillager"):
        {
            printf("NpcVillager\n");
            printf("Dream Revision: %d\n", dream_fhi.save_revision);
            printf("Main Revision: %d\n", main_fhi.save_revision);
            save_npc::save_npc_type type;
            auto npc = save_npc::get_save_npc(dream_buffer + dream_offset, dream_fhi.save_revision, main_fhi.header_revision, type);
            switch(type) {
            case save_npc::save_npc_type::type_1: 
            {
                printf("type_1\n");
                //util::write_data(main_buffer + main_offset, 0, (*npc.get())->get_everything(), main_size);
            }
                break;
            case save_npc::save_npc_type::type_2: 
            {
                printf("type_2\n");
                //util::write_data(main_buffer + main_offset, 0, ((save_npc::save_npc_2 *)(*npc.get()))->get_everything(), main_size);
            }

                break;
            case save_npc::save_npc_type::type_3:
            {
                printf("type_3\n");
                // util::write_data(main_buffer + main_offset, 0, ((save_npc::save_npc_3 *)(*npc.get()))->get_everything(), main_size);
                // for (int i = 0; i < 0x40; i++)
                // {
                //     printf("%02X ", *(((save_npc::save_npc_3 *)(*npc.get()))->get_everything() + i));
                //     if((i % 16) == 15) printf("\n");
                // }
            }
                break;
            default:
                printf("none\n");
                break;
            }
        }
            break;
        // case MurmurHash3::Calc_CEval("LandTime"):
        // {
        //     save_land_time::save_land_time_type type;
        //     auto time = save_land_time::get_save_land_time(dream_buffer + dream_offset, dream_fhi.save_revision, main_fhi.header_revision, type);
        //     switch(type) {
        //     case save_land_time::save_land_time_type::type_1:
        //         util::write_data(main_buffer + main_offset, 0, (*time.get())->to_bin(), main_size);
        //         break;
        //     case save_land_time::save_land_time_type::type_2:
        //         util::write_data(main_buffer + main_offset, 0, ((save_land_time::save_land_time_2 *)(*time.get()))->to_bin(), main_size);
        //         break;
        //     default:
        //         break;
        //     }
        // }
        //     break;
        // case MurmurHash3::Calc_CEval("LandMyDesign"):
        // {
        //     save_land_my_design::save_land_my_design_type type;
        //     auto time = save_land_my_design::get_save_land_my_design(dream_buffer + dream_offset, dream_fhi.save_revision, main_fhi.header_revision, type);
        //     switch(type) {
        //     case save_land_my_design::save_land_my_design_type::type_1:
        //         util::write_data(main_buffer + main_offset, 0, (*time.get())->to_bin(), main_size);
        //         break;
        //     case save_land_my_design::save_land_my_design_type::type_2:
        //         util::write_data(main_buffer + main_offset, 0, ((save_land_my_design::save_land_my_design_2 *)(*time.get()))->to_bin(), main_size);
        //         break;
        //     default:
        //         break;
        //     }
        // }
        //     break;
        // case MurmurHash3::Calc_CEval("PlayerHouseList"):
        // {
        //     save_player_house::save_player_house_type type;
        //     auto player_house_list = save_player_house::get_save_player_house_list(dream_buffer + dream_offset, dream_fhi.save_revision, main_fhi.header_revision, type);
        //     for(int house_index = 0; house_index < player_house_list.size(); house_index++) {
        //         switch(type) {
        //         case save_player_house::save_player_house_type::type_1:
        //         {
        //             util::write_data(main_buffer + main_offset + (house_index * save_player_house::save_player_house_1::get_size()), 0, (*player_house_list[house_index].get())->get_everything(), save_player_house::save_player_house_1::get_size());
        //         }
        //             break;
        //         case save_player_house::save_player_house_type::type_2:
        //         {
        //             util::write_data(main_buffer + main_offset + (house_index * save_player_house::save_player_house_2::get_size()), 0, ((save_player_house::save_player_house_2 *)(*player_house_list[house_index].get()))->get_everything(), save_player_house::save_player_house_2::get_size());
        //         }
        //             break;
        //         default:
        //             break;
        //         }
        //     }
        // }
        //     break;
        // case MurmurHash3::Calc_CEval("NpcHouseList"):
        // {
        //     save_npc_house::save_npc_house_type type;
        //     auto npc_house_list = save_npc_house::get_save_npc_house_list(dream_buffer + dream_offset, dream_fhi.save_revision, main_fhi.header_revision, type);
        //     for(int house_index = 0; house_index < npc_house_list.size(); house_index++) {
        //         switch(type) {
        //         case save_npc_house::save_npc_house_type::type_1:
        //         {
        //             util::write_data(main_buffer + main_offset + (house_index * save_npc_house::save_npc_house_1::get_size()), 0, (*npc_house_list[house_index].get())->get_everything(), save_npc_house::save_npc_house_1::get_size());
        //         }
        //             break;
        //         case save_npc_house::save_npc_house_type::type_2:
        //         {
        //             util::write_data(main_buffer + main_offset + (house_index * save_npc_house::save_npc_house_2::get_size()), 0, ((save_npc_house::save_npc_house_2 *)(*npc_house_list[house_index].get()))->get_everything(), save_npc_house::save_npc_house_2::get_size());
        //         }
        //             break;
        //         default:
        //             break;
        //         }
        //     }
        // }
        //     break;
        default:
            util::write_data(main_buffer + main_offset, 0, dream_buffer + dream_offset, min(main_size, dream_size));
            break;
        }
    }
    main_file.open(main_file_path, ios::out | ios::binary);
    util::write_data((ofstream &)main_file, 0, main_buffer, main_file_size);
    main_file.close();
}

/*
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
        
        util::write_data(player_buffer, SaveHeaderSize, dream_buffer + mainSize + (playerSize * i), playerSize);
        u8 house_level = 0;
        util::read_data(land_main_buffer, SaveHeaderSize + houseLvlOffset +  (i * houseSize), &house_level, sizeof(u8));

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
        u16 value = fix.second;
        util::write_data(main_buffer, SaveHeaderSize + EventFlagOffset + (fix.first * 2), &value, sizeof(u16));
    }
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
