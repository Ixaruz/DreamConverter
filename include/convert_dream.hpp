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
    u32 main_size = NULL;
    u32 dream_main_size = NULL;
    u32 player_size = NULL;
    u32 dream_player_size = NULL;
    u32 event_flag_land_offset = NULL;
    u32 dream_event_flag_land_offset = NULL;
    u32 event_flag_player_offset = NULL;
    u32 dream_event_flag_player_offset = NULL;
    u32 speciality_fruit_offset = NULL;
    u32 dream_speciality_fruit_offset = NULL;
    // PlayerOther (not available in dream)
    u32 item_collect_bit_offset = NULL;
    u32 recipe_collect_bit_offset = NULL;
    u32 storage_size_offset = NULL;
    u32 pocket_1_size_offset = NULL;
    u32 expand_baggage_offset = NULL;
    void setup_(fs::path &executable_path);
public:
    convert_dream(fs::path &executable_path, fs::path &template_path, fs::path &dream_path);
    void copy_data(fs::path &out_path, fs::path &dream_file_path);
    void fix_main(void *main_buffer);
    void fix_player(void *player_buffer, void *dream_player_buffer,  u8 house_level);
    void edit_item_collect_bit(void *player_buffer, u16 collect_bit_offset, bool value);
    void edit_recipe_bit(void *player_buffer, u16 collect_bit_offset, bool value);
};
