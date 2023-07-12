#pragma once
#include <types.hpp>
#include <util.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace template_check {
	typedef struct {
        /* 0x00 */ u32 major;
        /* 0x04 */ u32 minor;
        /* 0x08 */ u16 unk1;
        /* 0x0A */ u16 header_revision;
        /* 0x0C */ u16 unk2;
        /* 0x0E */ u16 save_revision;
    } file_header_info;

    enum class error {
        none,
        template_missing_files,
        template_wrong_revision,
        template_not_enough_players,
    };

    struct result {
        error error_type;
        string additional_info;
    };

    extern const vector<file_header_info*> revision_info;
        
    class template_check {
    private:
        fs::path templ_path;
        bool *g_players = nullptr;
        bool personalfound[8] = { false };
        result res = { error::none, "" };

        void check_players() {
            static string playernumbers = "";
            for (u8 player = 0; player < 8; player++) {
                if (g_players[player]) {
                    fs::path villager_folder = templ_path / ("Villager" + to_string(player));
                    if(!fs::exists(villager_folder)) {
                        res.error_type = error::template_not_enough_players;
                        playernumbers.append((playernumbers.empty() ? "" : ", ") + to_string(player));
                    }
                }
            }
            res.additional_info = playernumbers;
        }

    public:
        template_check(filesystem::path template_path, bool* players) {
            templ_path = fs::path(template_path);
            g_players = players;
        }
        
        result check_template_files(bool is_sub_dir = false);
        
        result check_template_files(fs::path file_path, bool is_sub_dir = false);
    };
}