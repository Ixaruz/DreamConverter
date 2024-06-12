#pragma once
#include <filesystem>
#include <fstream>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
#include <map>
#include <functional>
#include <types.hpp>
#include <MurmurHash3.hpp>

using namespace std;
namespace fs = std::filesystem;

const s32 dream_header_size = 0x830;
const s32 save_header_size = 0x110;
const s32 dream_header_difference = dream_header_size - save_header_size;

const u32 main_field_type =     MurmurHash3::Calc_CEval("::Game::SaveMain");
const u32 personal_field_type = MurmurHash3::Calc_CEval("::Game::SavePersonal");

const vector<vector<u32>> main_fields_to_copy {
    //changed in 1.1.0 (+0x10); -> alignment change; size of _d35a9251 changed from 0x4 (w Alignment !!!!0x8!!!!) to 0x8 (w Alignment !!!!0x10!!!!); NpcVillager(what we're interested in) didnt change; (due to alignment there are 0x8 more bytes afterwards)
    //1.5.0 (bigger change); -> type "Animal" grew by 0x780 (160 LightMemories; added ClothesPTops and some other stuff (what item did someone wear when they visited???); size 0x8 w Alignment 0xC); effective size increase: 0x780 * 24 = 0xB400
    //1.10.0(+0x10), -> added "BirthdayPlantFtr" at the end (8 byte * 2); we can ignore this
    //2.0.0(another bigger change) -> NpcArchive went from count 400 to 420 (blaze it) (0x1220); added "BirthdayAudioFtr" (8 bytes) and "BirthdayLampFtr" (8 bytes)
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("Npc"), MurmurHash3::Calc_CEval("NpcVillager")}, //don't fit //handled by save_npc.hpp
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("PlayerVillagerAccountTable"), MurmurHash3::Calc_CEval("AccountTable")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("Weather")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("LandTime")}, //don't fit //handled by save_land_time.hpp //changed in 2.0.0
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("LandId")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("LandMyDesign")}, //don't fit //handled by save_land_my_design.hpp //changed in 1.9.0
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("EventFlag")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("MainField")}, //don't fit //handled by save_main_field.hpp //changed in 2.0.0
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("PlayerHouseList")}, //don't fit //handled by save_player_house_list.hpp //changed in 2.0.0
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("NpcHouseList")}, //don't fit //handled by save_npc_house_list.hpp //changed in 2.0.0
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("Shop")}, //don't fit // all shops changed size; exception: ShopKabu; added ShopGardening, ShopGallery, ShopCommune //changed in 1.2.0; 1.5.0; 1.6.0; 1.7.0; 1.9.0; 2.0.0
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("Museum")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("VisitorNpc")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("SnowManFamily")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("Fg")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("ItemMarketingRoute")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("VillageMelody")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("Office")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("BulletinBoard")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("RegionLanguage")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("CalendarEventRegion")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("CampSite")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("NpcCamp")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("AirportThemeColor")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("RumorFavorite")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("PublicWorksLoan")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("PublicWorksName")}, //fits
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("VillageScore")}, //fits
    /*{MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("NetLandProfile")},*/ //fits (after 1.4.0 aka dream update) //dont copy this
    {MurmurHash3::Calc_CEval("Land"), MurmurHash3::Calc_CEval("SettlerQuest")}, //introduced in 1.4.0 for some bizarro reason?
};

const vector<vector<u32>> personal_fields_to_copy {
    {MurmurHash3::Calc_CEval("Player"), 3545928273 /*_d35a9251*/ /*Code : u32*/},
    {MurmurHash3::Calc_CEval("Player"), 419281215 /*_d35a9251*/ /*s8*/},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("LookPack")},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("PlayerId")},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("EventFlag")},
    //added 0x200 * 6 "OpenProfile" (can be ignored)
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("LifeSupport")}, //don't fit //changed in 1.5.0; size += 0xC00 ("OpenProfile"; 2d array of bools for *squints* something?)
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("BirthDay")},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("PastDaysFromMade")},
    /*{MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("NetProfile")},*/ //don't fit //changed in 2.0.0; size += 0x2
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("ProfileMain")},
    {MurmurHash3::Calc_CEval("Player"), 1562364676 /*_5d1fcb04*/ /*u8*/},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("LastPlayDate")},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("LastBirthdayYear")},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("BirthdayLiveDate")},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("BirthdayLiveMsgList")},
    {MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("GalleryLandId")},
    /*{MurmurHash3::Calc_CEval("Player"), MurmurHash3::Calc_CEval("PreviousLandId")},*/ //don't fit //introduced in 1.5.0
};

const vector<u16> mainmenu_recipes = vector<u16>{
        0x00A, //flimsy axe
        0x00D, //campfire
        0x015, //flimsy fishing rod
        0x016, //flimsy net
        0x06B, //ladder
};

const vector<u16> pretty_good_tools_recipes_recipes = vector<u16>{
        0x10F, //axe
        0x118, //watering can
        0x119, //shovel
        0x11A, //fishing rod
        0x11B, //net
        0x11D, //stone axe
};

const vector<u16> be_a_chef_recipes = vector<u16>{
        0x34C, //carrot potage
        0x387, //flour
        0x38A, //sugar
        0x3A4, //tomato curry
        0x3A5, //pumpkin bagel sandwich
        0x3A9, //pancakes
        0x3B1, //grilled sea bass with herbs
        0x410, // stonework kitchen
};

const map<u16, u16> town_fruit_smoothies_map = {
    {2213, 0x38D}, //apple smoothie
    {2214, 0x38E}, //orange smoothie
    {2285, 0x388}, //pear smoothie
    {2286, 0x38C}, //peach smoothie
    {2287, 0x384}, //cherry smoothie
};

const map<u16, u16> dream_land_event_flags = {
    {346, 0}, //IsDreamingBed
    {354, 1}, //TapDreamEnable
    {362, 0}, // EnableMyDream
    {364, 0}, //DreamUploadPlayerHaveCreatorID
};

const vector<u16> dream_player_event_flags = {
    171, //MainmenuRecipe
    559, //HairStyleColor1
    560, //HairStyleColor2
    561, //HairStyleColor3
    565, //GetLicenses1
    566, //GetLicenses2
    567, //GetLicenses3
    568, //GetLicenses4
    569, //GetLicenses5
    570, //GetLicenses6
    571, //GetLicenses7
    572, //GetLicenses8
    573, //GetLicenses9
    610, //ItemRingEnable
    644, //GetLicenseGrdMydesign
    669, //UpgradePocket30
    670, //UpgradePocket40
    714, //UnlockMyDesignProCategory
    759, //P2_CreatedAfterOwlMoving
    760, //OwlGotDiyRecipe
    1142, //AddHalloweenColor1
    1143, //AddHalloweenColor2
    1144, //AddHalloweenColor3
    1172, //UnlockMydesignPro2
    1219, //AddHairStyle4
    1410, //MainmenuRecipe_v2
    1448, //MainmenuMydesignPatternPlus
    1450, //MainmenuCamera1stPersonView
    1452, //UnlockInterior_CeilingFurniture
    1453, //FenceRemakeEnable
    1458, //RcoStorageExpansion_v200_AddLevel
    1538, //MainmenuTips
    1567, //UnlockPlayerHair37
    1568, //UnlockPlayerHair38
    1569, //UnlockPlayerHair39
    1570, //UnlockPlayerHair40
    1571, //UnlockPlayerHair41
    1572, //UnlockPlayerHair42
    1573, //UnlockPlayerHair43
    1574, //UnlockPlayerHair44
    1575, //UnlockPlayerHair45
    1576, //UnlockPlayerHair46
    1577, //UnlockPlayerHair47
};

const map<u16, u16> dream_player_event_flags_collect_item_map = {
    {559, 0x2359}, //HairStyles
    {560, 0x235A},
    {561, 0x235B},
    {565, 0x2245}, //GetLicenses
    {566, 0x2246},
    {567, 0x2247},
    {568, 0x2248},
    {569, 0x2249},
    {570, 0x224A},
    {571, 0x224B},
    {572, 0x224C},
    {573, 0x224D},
    {610, 0x2590}, //ToolRingItsEssential
    {644, 0x262B}, //CustomDesignPathPermit
    {669, 0x235C}, //UpgradePocket30
    {670, 0x2B84}, //UpgradePocket40
    {714, 0x2F99}, //CustomDesignProEditor
    {1142, 0x33C8},//HalloweenCharacterColors
    {1143, 0x33C9},
    {1144, 0x33CA},
    {1172, 0x338B},//CustomDesignProEditorPlus
    {1219, 0x35C6},//StylishHairStyles
    {1410, 0x3963},//Update200RecipeLicenseApp
    {1448, 0x3964},
    {1452, 0x3965},
    {1453, 0x3966},
    {1450, 0x3967},
    {1538, 0x39CC},//IslandLife101Service
    {1567, 0x39ED},//Top4FabHairstyles
};

const u32 storage_sizes[] = {
    0,
    80,
    120,
    240,
    320,
    400,
    800,
    1600,
    2400,
    3200,
    4000,
    5000
};

namespace util
{
    void set_bit(void *buffer, int bit_offset, bool value);

    void read_32(ifstream &file, u32 offset, u32 &value);

    void read_32(void *buffer, u32 offset, u32 &value);

    void write_32(ofstream &file, u32 offset, u32 value);

    void write_32(void *buffer, u32 offset, u32 value);

    void read_data(ifstream &file, u32 offset, void *value, u32 size);

    void read_data(void *buffer, u32 offset, void *value, u32 size);

    void write_data(ofstream &file, u32 offset, void *value, u32 size);

    void write_data(void *buffer, u32 offset, void *value, u32 size);

    string get_folder_name(fs::path path);
}
