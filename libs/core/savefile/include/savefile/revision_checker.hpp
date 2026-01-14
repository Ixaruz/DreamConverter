#pragma once
#include "file_hash_revision.hpp"

#include <types.hpp>
#include <vector>

namespace revision_checker{
    struct save_file_sizes
    {
        u32 Main;
        u32 Personal;
        u32 PhotoStudioIsland;
        u32 PostBox;
        u32 Profile;
        u32 WhereAreN = 0;
    };

    static std::vector<save_file_sizes*> sizes_by_revision = std::vector<save_file_sizes*>
    {
        new save_file_sizes{REV_100_MAIN, REV_100_PERSONAL, REV_100_PHOTO, REV_100_POSTBOX, REV_100_PROFILE}, // 1.0.0
        new save_file_sizes{REV_110_MAIN, REV_110_PERSONAL, REV_110_PHOTO, REV_110_POSTBOX, REV_110_PROFILE}, // 1.1.0
        new save_file_sizes{REV_120_MAIN, REV_120_PERSONAL, REV_120_PHOTO, REV_120_POSTBOX, REV_120_PROFILE}, // 1.2.0
        new save_file_sizes{REV_130_MAIN, REV_130_PERSONAL, REV_130_PHOTO, REV_130_POSTBOX, REV_130_PROFILE}, // 1.3.0
        new save_file_sizes{REV_140_MAIN, REV_140_PERSONAL, REV_140_PHOTO, REV_140_POSTBOX, REV_140_PROFILE}, // 1.4.0
        new save_file_sizes{REV_150_MAIN, REV_150_PERSONAL, REV_150_PHOTO, REV_150_POSTBOX, REV_150_PROFILE}, // 1.5.0
        new save_file_sizes{REV_160_MAIN, REV_160_PERSONAL, REV_160_PHOTO, REV_160_POSTBOX, REV_160_PROFILE}, // 1.6.0
        new save_file_sizes{REV_170_MAIN, REV_170_PERSONAL, REV_170_PHOTO, REV_170_POSTBOX, REV_170_PROFILE}, // 1.7.0
        new save_file_sizes{REV_180_MAIN, REV_180_PERSONAL, REV_180_PHOTO, REV_180_POSTBOX, REV_180_PROFILE}, // 1.8.0
        new save_file_sizes{REV_190_MAIN, REV_190_PERSONAL, REV_190_PHOTO, REV_190_POSTBOX, REV_190_PROFILE}, // 1.9.0
        new save_file_sizes{REV_1100_MAIN,REV_1100_PERSONAL,REV_1100_PHOTO,REV_1100_POSTBOX,REV_1100_PROFILE},// 1.10.0
        new save_file_sizes{REV_1110_MAIN,REV_1110_PERSONAL,REV_1110_PHOTO,REV_1110_POSTBOX,REV_1110_PROFILE},// 1.11.0
        new save_file_sizes{REV_200_MAIN, REV_200_PERSONAL, REV_200_PHOTO, REV_200_POSTBOX, REV_200_PROFILE, REV_200_WHEREAREN}, // 2.0.0
        new save_file_sizes{REV_300_MAIN, REV_300_PERSONAL, REV_300_PHOTO, REV_300_POSTBOX, REV_300_PROFILE, REV_300_WHEREAREN}, // 3.0.0
    };

    typedef struct {
    /* 0x00 */ u32 major;
    /* 0x04 */ u32 minor;
    /* 0x08 */ u16 unk1;
    /* 0x0A */ u16 header_revision;
    /* 0x0C */ u16 unk2;
    /* 0x0E */ u16 save_revision;
    } file_header_info;

    //we dont support anything before 1.4.0 (dream update)
    static std::vector<file_header_info> revision_info = std::vector<file_header_info>
    {
        /*
        file_header_info { 0x00067, 0x0006F, 2, 0, 2,  0 }, // 1.0.0
        file_header_info { 0x0006D, 0x00078, 2, 0, 2,  1 }, // 1.1.0
        file_header_info { 0x0006D, 0x00078, 2, 0, 2,  2 }, // 1.1.1
        file_header_info { 0x0006D, 0x00078, 2, 0, 2,  3 }, // 1.1.2
        file_header_info { 0x0006D, 0x00078, 2, 0, 2,  4 }, // 1.1.3
        file_header_info { 0x0006D, 0x00078, 2, 0, 2,  5 }, // 1.1.4
        file_header_info { 0x20006, 0x20008, 2, 0, 2,  6 }, // 1.2.0
        file_header_info { 0x20006, 0x20008, 2, 0, 2,  7 }, // 1.2.1
        file_header_info { 0x40002, 0x40008, 2, 0, 2,  8 }, // 1.3.0
        file_header_info { 0x40002, 0x40008, 2, 0, 2,  9 }, // 1.3.1
        */
        file_header_info { 0x50001, 0x5000B, 2, 0, 2, 10 }, // 1.4.0
        file_header_info { 0x50001, 0x5000B, 2, 0, 2, 11 }, // 1.4.1
        file_header_info { 0x50001, 0x5000B, 2, 0, 2, 12 }, // 1.4.2
        file_header_info { 0x60001, 0x6000C, 2, 0, 2, 13 }, // 1.5.0
        file_header_info { 0x60001, 0x6000C, 2, 0, 2, 14 }, // 1.5.1
        file_header_info { 0x70001, 0x70006, 2, 0, 2, 15 }, // 1.6.0
        file_header_info { 0x74001, 0x74005, 2, 0, 2, 16 }, // 1.7.0
        file_header_info { 0x78001, 0x78001, 2, 0, 2, 17 }, // 1.8.0
        file_header_info { 0x7C001, 0x7C006, 2, 0, 2, 18 }, // 1.9.0
        file_header_info { 0x7D001, 0x7D004, 2, 0, 2, 19 }, // 1.10.0
        file_header_info { 0x7E001, 0x7E001, 2, 0, 2, 20 }, // 1.11.0
        file_header_info { 0x7E001, 0x7E001, 2, 0, 2, 21 }, // 1.11.1
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 22 }, // 2.0.0
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 23 }, // 2.0.1
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 24 }, // 2.0.2
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 25 }, // 2.0.3
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 26 }, // 2.0.4
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 27 }, // 2.0.5
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 28 }, // 2.0.6
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 29 }, // 2.0.7
        file_header_info { 0x80009, 0x80085, 2, 0, 2, 30 }, // 2.0.8
        file_header_info { 0xA0002, 0xA0028, 2, 0, 2, 31 }, // 3.0.0
    };

    inline static file_header_info get_revision_info_by_save_revision(int revision) {
        return revision_info[revision - 10]; // -10 for the commented out versions
    }

    static std::vector<save_file_sizes*> size_info = std::vector<save_file_sizes*>
    {
        sizes_by_revision[0], // 1.0.0
        sizes_by_revision[1], // 1.1.0
        sizes_by_revision[1], // 1.1.1
        sizes_by_revision[1], // 1.1.2
        sizes_by_revision[1], // 1.1.3
        sizes_by_revision[1], // 1.1.4
        sizes_by_revision[2], // 1.2.0
        sizes_by_revision[2], // 1.2.1
        sizes_by_revision[3], // 1.3.0
        sizes_by_revision[3], // 1.3.1
        sizes_by_revision[4], // 1.4.0
        sizes_by_revision[4], // 1.4.1
        sizes_by_revision[4], // 1.4.2
        sizes_by_revision[5], // 1.5.0
        sizes_by_revision[5], // 1.5.1
        sizes_by_revision[6], // 1.6.0
        sizes_by_revision[7], // 1.7.0
        sizes_by_revision[8], // 1.8.0
        sizes_by_revision[9], // 1.9.0
        sizes_by_revision[10], // 1.10.0
        sizes_by_revision[11], // 1.11.0
        sizes_by_revision[11], // 1.11.1
        sizes_by_revision[12], // 2.0.0
        sizes_by_revision[12], // 2.0.1
        sizes_by_revision[12], // 2.0.2
        sizes_by_revision[12], // 2.0.3
        sizes_by_revision[12], // 2.0.4
        sizes_by_revision[12], // 2.0.5
        sizes_by_revision[12], // 2.0.6
        sizes_by_revision[12], // 2.0.7
        sizes_by_revision[12], // 2.0.8
        sizes_by_revision[13], // 3.0.0
    };

    static std::vector<file_hash_info> hash_info = std::vector<file_hash_info>
    {
        REV_100, // 1.0.0
        REV_110, // 1.1.0
        REV_110, // 1.1.1
        REV_110, // 1.1.2
        REV_110, // 1.1.3
        REV_110, // 1.1.4
        REV_120, // 1.2.0
        REV_120, // 1.2.1
        REV_130, // 1.3.0
        REV_130, // 1.3.1
        REV_140, // 1.4.0
        REV_140, // 1.4.1
        REV_140, // 1.4.2
        REV_150, // 1.5.0
        REV_150, // 1.5.1
        REV_160, // 1.6.0
        REV_170, // 1.7.0
        REV_180, // 1.8.0
        REV_190, // 1.9.0
        REV_1100, // 1.10.0
        REV_1110, // 1.11.0
        REV_1110, // 1.11.1
        REV_200, // 2.0.0
        REV_200, // 2.0.1
        REV_200, // 2.0.2
        REV_200, // 2.0.3
        REV_200, // 2.0.4
        REV_200, // 2.0.5
        REV_200, // 2.0.6
        REV_200, // 2.0.7
        REV_200, // 2.0.8
        REV_300, // 3.0.0
    };
}
