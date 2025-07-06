#pragma once
#include "generated_offsets.hpp"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;
class convert_dream {
private:
    bool g_players[8]{false};
    size_t player_count = 0;
    fs::path dream_file_path;

    revision_checker::file_header_info main_fhi;
    revision_checker::file_header_info dream_fhi;

    Smmh::Land::VersionedOffsets main_yaml;
    Smmh::Land::VersionedOffsets dream_yaml;
    Smmh::Player::VersionedOffsets player_yaml;
    Smmh::Player::VersionedOffsets dream_player_yaml;
    Smmh::PlayerOther::VersionedOffsets player_other_yaml;
    Smmh::PlayerOther::VersionedOffsets dream_player_other_yaml;
    void copy_data_(fs::path &out_path, fs::path &dream_file_path);
    void write_landname_(void *dream_buffer, ofstream &landname_file);
    void fix_main_(void *main_buffer);
    void fix_player_(void *player_buffer,
                     void *dream_player_buffer,
                     u8 house_level,
                     void const *net_profile_buffer,
                     void const *profile_buffer);
    void edit_item_collect_bit_(void *player_buffer, u16 collect_bit_offset, bool value);
    void edit_recipe_bit_(void *player_buffer, u16 collect_bit_offset, bool value);
public:
    convert_dream(fs::path &executable_path, fs::path &template_path, fs::path &dream_path);
};
