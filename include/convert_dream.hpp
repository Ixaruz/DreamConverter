#pragma once
#include <savefile.hpp>
#include <iostream>

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
    account_table acc_table;
    void get_account_table(void *main_file_buffer) {
        util::read_data(main_file_buffer, SaveHeaderSize + GSavePlayerVillagerAccountOffset - GAccountTableOffset, &acc_table, sizeof(acc_table));
    }
public:
    convert_dream(fs::path &template_path, fs::path &dream_path);
    void copy_data(fs::path &out_path, fs::path &dream_file_path);
    void fix_main(void *main_buffer);
    void fix_player(void *player_buffer, void *dream_player_buffer,  u8 house_level);
    void edit_item_collect_bit(void *player_buffer, u16 collect_bit_offset, bool value);
    void edit_recipe_bit(void *player_buffer, u16 collect_bit_offset, bool value);
};