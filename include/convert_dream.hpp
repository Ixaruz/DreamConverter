#pragma once
#include "util.hpp"
#include "savefile.hpp"
#include "smmh_paths_by_revision.hpp"
#include "save_npc.hpp"
#include "save_land_my_design.hpp"
#include "save_land_time.hpp"
#include "save_main_field.hpp"
#include "save_npc_house_list.hpp"
#include "save_player_house_list.hpp"
#include "save_shop.hpp"
#include <ACNHByaml.hpp>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;
namespace fs = std::filesystem;
class convert_dream {
private:
    bool g_players[8]{false};
    size_t player_count = 0;
    fs::path dream_file_path;

    revision_checker::file_header_info main_fhi;
    revision_checker::file_header_info dream_fhi;
    ACNHByaml *main_yaml = nullptr;
    ACNHByaml *dream_yaml = nullptr;
    u64 main_size;
    u64 dream_main_size;
    u64 player_size;
    u64 dream_player_size;
    u64 dream_town_name_size;
    u64 dream_town_name_offset;
    u64 event_flag_land_offset;
    u64 dream_event_flag_land_offset;
    u64 event_flag_player_offset;
    u64 dream_event_flag_player_offset;
    u64 speciality_fruit_offset;
    u64 dream_speciality_fruit_offset;
    u64 net_land_profile_offset;
    u64 net_land_profile_size;
    // PlayerOther (not available in dream)
    u64 item_collect_bit_offset;
    u64 recipe_collect_bit_offset;
    u64 storage_size_offset;
    u64 pocket_1_size_offset;
    u64 expand_baggage_offset;
    void setup_(fs::path &executable_path);
    void copy_data_(fs::path &out_path, fs::path &dream_file_path);
    void write_landname_(void *dream_buffer, ofstream &landname_file);
    void fix_main_(void *main_buffer);
    void fix_player_(void *player_buffer, void *dream_player_buffer,  u8 house_level);
    void edit_item_collect_bit_(void *player_buffer, u16 collect_bit_offset, bool value);
    void edit_recipe_bit_(void *player_buffer, u16 collect_bit_offset, bool value);
public:
    convert_dream(fs::path &executable_path, fs::path &template_path, fs::path &dream_path);
};
