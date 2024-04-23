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
#include <ACNHByaml.hpp>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;
namespace fs = std::filesystem;

typedef struct {
    u8 acc[GSavePlayerVillagerAccountSize];
} account; //0x48

typedef struct {
    u8 offs[GAccountTableOffset]; // 0x10
    account accs[8]; // 0x48 * 8
} account_table; // 0x250

class convert_dream {
private:
    bool g_players[8] = {false};
    size_t player_count = 0;
    fs::path dream_file_path;

    revision_checker::file_header_info main_fhi;
    revision_checker::file_header_info dream_fhi;
    ACNHByaml *main_yaml = nullptr;
    ACNHByaml *dream_yaml = nullptr;

public:
    convert_dream(fs::path &executable_path, fs::path &template_path, fs::path &dream_path);
    void copy_data(fs::path &out_path, fs::path &dream_file_path);
    void fix_main(void *main_buffer);
    void fix_player(void *player_buffer, void *dream_player_buffer,  u8 house_level);
    void edit_item_collect_bit(void *player_buffer, u16 collect_bit_offset, bool value);
    void edit_recipe_bit(void *player_buffer, u16 collect_bit_offset, bool value);
};
