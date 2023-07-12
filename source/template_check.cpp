#include <template_check.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace template_check {

    extern const vector<file_header_info*> revision_info = vector<file_header_info*>{
        new file_header_info { /*Major*/ 0x80009, /*Minor*/ 0x80085, /*Unk1*/ 2, /*HeaderRevision*/ 0, /*Unk2*/ 2, /*SaveRevision*/ 22}, // 2.0.0
        new file_header_info { /*Major*/ 0x80009, /*Minor*/ 0x80085, /*Unk1*/ 2, /*HeaderRevision*/ 0, /*Unk2*/ 2, /*SaveRevision*/ 23}, // 2.0.1
        new file_header_info { /*Major*/ 0x80009, /*Minor*/ 0x80085, /*Unk1*/ 2, /*HeaderRevision*/ 0, /*Unk2*/ 2, /*SaveRevision*/ 24}, // 2.0.2
        new file_header_info { /*Major*/ 0x80009, /*Minor*/ 0x80085, /*Unk1*/ 2, /*HeaderRevision*/ 0, /*Unk2*/ 2, /*SaveRevision*/ 25}, // 2.0.3
        new file_header_info { /*Major*/ 0x80009, /*Minor*/ 0x80085, /*Unk1*/ 2, /*HeaderRevision*/ 0, /*Unk2*/ 2, /*SaveRevision*/ 26}, // 2.0.4
        new file_header_info { /*Major*/ 0x80009, /*Minor*/ 0x80085, /*Unk1*/ 2, /*HeaderRevision*/ 0, /*Unk2*/ 2, /*SaveRevision*/ 27}, // 2.0.5
        new file_header_info { /*Major*/ 0x80009, /*Minor*/ 0x80085, /*Unk1*/ 2, /*HeaderRevision*/ 0, /*Unk2*/ 2, /*SaveRevision*/ 28}, // 2.0.6
    };

    result template_check::check_template_files(bool is_sub_dir) {return template_check::check_template_files(templ_path, is_sub_dir);}
    
    result template_check::check_template_files(fs::path file_path, bool is_sub_dir) {

        if (!is_sub_dir) {
            check_players();
            if(res.error_type != error::none) return res;
        }

        u32 items_count = 0;
        bool main_found = false;
        bool correct_revision = false;


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
                    file_header_info header_file_file_header_info;
                    ifstream header_file;
                    header_file.open(dir_entry.path(), ios::in | ios::binary);
                    util::read_data(header_file, 0, &header_file_file_header_info, sizeof(file_header_info));
                    header_file.close();
                    for (auto& r : revision_info) {
                        if (memcmp(r, &header_file_file_header_info, sizeof(file_header_info)) == 0) {
                            correct_revision = true;
                            //printf("M: 0x%X M = 0x%X rev = %2u \t", header_file_file_header_info.major, header_file_file_header_info.minor, header_file_file_header_info.save_revision);
                        }
                    }
                    if (!correct_revision) {
                        res.error_type = error::template_wrong_revision;
                        char revision[50];
                        std::snprintf(revision, 50, "M = 0x%X, m = 0x%X, rev = %2u", header_file_file_header_info.major, header_file_file_header_info.minor, header_file_file_header_info.save_revision);
                        res.additional_info = string(revision);
                        return res;
                    }
                }
            }
        }

        if (!is_sub_dir && !main_found) {
            res.error_type = error::template_missing_files;
            cout << "main missing" << endl;
        }

        if ((items_count % 2) == 1) {
            res.error_type = error::template_missing_files;
            cout << "items_count not divisible by two" << endl;
            cout << (int)items_count << endl;
            cout << file_path.generic_string() << endl;
        }

        return res;
    }
}