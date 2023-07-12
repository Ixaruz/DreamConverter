#pragma once
#include <SaveCrypto.hpp>
#include <MurmurHash3.hpp>
#include <file_hash_revision.hpp>
#include <template_check.hpp>
#include <util.hpp>
#include <regex>

using namespace std;
namespace fs = std::filesystem;

namespace savefile {
    bool load_metadata(fs::path dream_path, string &metadata);

    size_t read_player_count(fs::path dream_path);

    bool is_file_size(fs::path file, size_t size);

    void decrypt_pair(fs::path data_path, fs::path header_path, fs::path data_path_out);

    void encrypt_pair(fs::path data_path, fs::path header_path_out, fs::path data_path_out, u32 tick);

    void calc_file_hash(fs::path data_path);

    void decrypt_batch(fs::path in_path, fs::path out_path, bool *g_players);

    void encrypt_batch(fs::path in_path, fs::path out_path, u32 tick);

    void check_players(ifstream &dream_file, bool *g_players);

    vector<fs::path> get_player_folders(fs::path folder, bool *g_players);
}