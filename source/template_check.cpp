#include <template_check.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace template_check {

    void template_check::check_players(){
        static string playernumbers = "";
        for (u8 player = 0; player < 8; player++) {
            if (g_players[player]) {
                fs::path villager_folder = templ_path / ("Villager" + to_string(player));
                if(!fs::exists(villager_folder)) {
                    res.error_type = error::not_enough_players;
                    playernumbers.append((playernumbers.empty() ? "" : ", ") + to_string(player));
                }
            }
        }
        res.additional_info = playernumbers;
    }

    result template_check::check_template_files(bool is_sub_dir) {return template_check::check_template_files(templ_path, is_sub_dir);}

    result template_check::check_template_files(fs::path file_path, bool is_sub_dir) {

        u32 items_count = 0;
        bool main_found = false;

        for (auto const& dir_entry : fs::directory_iterator(file_path))
        {
            if(fs::is_directory(dir_entry)){
                if(g_players[util::get_folder_name(dir_entry.path()).back() - '0']) {
                    //cout << "need to check directory:" << endl << dir_entry.path().generic_string() << endl;
                    res = check_template_files(dir_entry.path(), true);
                    if (res.error_type != error::none) {
                        return res;
                    }
                }
            }

            else if(dir_entry.path().filename().generic_string() == "landname.dat" || dir_entry.path().extension() != ".dat") {
                continue;
            }

            else if(fs::is_regular_file(dir_entry.path())){
                items_count++;
                if (dir_entry.path().filename().generic_string() == "main.dat") main_found = true;
                else if(dir_entry.path().generic_string().find("Header.dat") != string::npos) {
                    
                    revision_checker::file_header_info header_file_file_header_info;
                    ifstream header_file;
                    header_file.open(dir_entry.path(), ios::in | ios::binary);
                    util::read_data(header_file, 0, &header_file_file_header_info, sizeof(revision_checker::file_header_info));
                    header_file.close();

                    if(!revision_found) {
                        for (auto& r : revision_checker::revision_info) {
                            if (memcmp(r, &header_file_file_header_info, sizeof(revision_checker::file_header_info)) == 0) {
                                _file_header_info = header_file_file_header_info;
                                revision_found = true;
                                break;
                            }
                        }
                    }
                    else {
                        if (memcmp(&_file_header_info, &header_file_file_header_info, sizeof(revision_checker::file_header_info)) != 0) {
                            res.error_type = error::wrong_revision;
                            char revision[50];
                            std::snprintf(revision, 50, "M = 0x%X, m = 0x%X, rev = %2u", header_file_file_header_info.major, header_file_file_header_info.minor, header_file_file_header_info.save_revision);
                            res.additional_info = string(revision);
                            return res;
                        }
                    }
                }
            }
        }

        if (!is_sub_dir) {
            check_players();
            if(!main_found) {
                res.error_type = error::missing_files;
                cout << "main missing" << endl;
            }
            if(!revision_found) {
                res.error_type = error::wrong_revision;
                cout << "main missing" << endl;
            }
        }

        if ((items_count % 2) == 1) {
            res.error_type = error::missing_files;
            cout << "items_count not divisible by two" << endl;
            cout << (int)items_count << endl;
            cout << file_path.generic_string() << endl;
        }

        return res;
    }
}