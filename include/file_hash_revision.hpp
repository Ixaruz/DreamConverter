#include <file_hash_info.hpp>

const std::string FN_MAIN = "main.dat";
const std::string FN_PERSONAL = "personal.dat";
const std::string FN_POSTBOX = "postbox.dat";
const std::string FN_PHOTO = "photo_studio_island.dat";
const std::string FN_PROFILE = "profile.dat";
const std::string FN_WHEREAREN = "wherearen.dat";

const u32 REV_200_MAIN = 0x8F1BB0;
const u32 REV_200_PERSONAL = 0x6A520;
const u32 REV_200_POSTBOX = 0x64140;
const u32 REV_200_PHOTO = 0x2F650;
const u32 REV_200_PROFILE = 0x69560;
const u32 REV_200_WHEREAREN = 0xB8A4E0;

static file_hash_info REV_200 = file_hash_info(std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_200_MAIN, std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1e339c),
        new file_hash_region(0x1e34b0, 0x36406c),
        new file_hash_region(0x547630, 0x03693c),
        new file_hash_region(0x57df70, 0x033acc),
        new file_hash_region(0x5b1b50, 0x03693c),
        new file_hash_region(0x5e8490, 0x033acc),
        new file_hash_region(0x61c070, 0x03693c),
        new file_hash_region(0x6529b0, 0x033acc),
        new file_hash_region(0x686590, 0x03693c),
        new file_hash_region(0x6bced0, 0x033acc),
        new file_hash_region(0x6f0ab0, 0x03693c),
        new file_hash_region(0x7273f0, 0x033acc),
        new file_hash_region(0x75afd0, 0x03693c),
        new file_hash_region(0x791910, 0x033acc),
        new file_hash_region(0x7c54f0, 0x03693c),
        new file_hash_region(0x7fbe30, 0x033acc),
        new file_hash_region(0x82fa10, 0x03693c),
        new file_hash_region(0x866350, 0x033acc),
        new file_hash_region(0x899e20, 0x057d8c),
    }),
    new file_hash_details(FN_PERSONAL, REV_200_PERSONAL, std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x3693c),
        new file_hash_region(0x36a50, 0x33acc),
    }),
    new file_hash_details(FN_POSTBOX, REV_200_POSTBOX, std::vector<file_hash_region*>
    {
        new file_hash_region(0x100, 0x4732c),
    }),
    new file_hash_details(FN_PHOTO, REV_200_PHOTO, std::vector<file_hash_region*>
    {
        new file_hash_region(0x100, 0x2f54c),
    }),
    new file_hash_details(FN_PROFILE, REV_200_PROFILE, std::vector<file_hash_region*>
    {
        new file_hash_region(0x100, 0x6945c),
    }),
    new file_hash_details(FN_WHEREAREN, REV_200_WHEREAREN, std::vector<file_hash_region*>
    {
        new file_hash_region(0x100, 0xB8A3DC),
    }),
} );