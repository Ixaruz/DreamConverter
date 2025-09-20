#pragma once
#include "revision_checker.hpp"

#include <filesystem>

using namespace std;
namespace fs = std::filesystem;
namespace savefile {

    bool load_metadata(fs::path dream_path, string &metadata);

    u32 read_32_from_metadata(fs::path dream_path, string name);

    string read_string_from_metadata(fs::path dream_path, string name);

    size_t read_player_count(fs::path dream_path);

    string read_island_name(fs::path dream_path);

    bool is_file_size(fs::path file, size_t size);

    void decrypt_pair(fs::path data_path, fs::path header_path, fs::path data_path_out);

    void encrypt_pair(fs::path data_path, fs::path header_path_out, fs::path data_path_out, u32 tick);

    void calc_file_hash(fs::path data_path, u16 revision);

    void decrypt_batch(fs::path in_path, fs::path out_path, bool *g_players);

    void encrypt_batch(fs::path in_path, fs::path out_path, u32 tick, u16 revision);

    //checks if the two header infos use the same save file structure (Major Save versions)
    //return 0 if identical
    //return -1 if info 1 is older than info 2
    //return 1 if info 1 is newer than info 2
    int check_file_header_info_compatibility(revision_checker::file_header_info info_1, revision_checker::file_header_info info_2);
}
