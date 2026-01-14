#pragma once
#include "generated_offsets.hpp"
#include <types.hpp>
#include <map>
#include <vector>


using namespace std;

const s32 dream_header_size = 0x830;
const s32 save_header_size = 0x110;
const s32 dream_header_difference = dream_header_size - save_header_size;

struct FieldLandInfo {
    const char* name;
    const Smmh::OffsetSize Smmh::Land::VersionedOffsets::* member;
};

struct FieldPlayerInfo {
    const char* name;
    const Smmh::OffsetSize Smmh::Player::VersionedOffsets::* member;
};

constexpr FieldLandInfo main_fields_to_copy[] = {
    { "NpcVillager", &Smmh::Land::VersionedOffsets::NpcVillager },                                      //don't fit //handled by save_npc.hpp
    // Don't copy to keep account linkage
    // { "PlayerVillagerAccountTable", &Smmh::Land::VersionedOffsets::PlayerVillagerAccountTable },        //fits
    { "Weather", &Smmh::Land::VersionedOffsets::Weather },                                              //fits
    { "LandTime", &Smmh::Land::VersionedOffsets::LandTime },                                            //don't fit //handled by save_land_time.hpp //changed in 2.0.0
    { "LandId", &Smmh::Land::VersionedOffsets::LandId },                                                //fits
    { "LandMyDesign", &Smmh::Land::VersionedOffsets::LandMyDesign },                                    //don't fit //handled by save_land_my_design.hpp //changed in 1.9.0
    { "EventFlag", &Smmh::Land::VersionedOffsets::EventFlag },                                          //fits
    { "MainField", &Smmh::Land::VersionedOffsets::MainField },                                          //don't fit //handled by save_main_field.hpp //changed in 2.0.0
    { "PlayerHouseList", &Smmh::Land::VersionedOffsets::PlayerHouseList },                              //don't fit //handled by save_player_house_list.hpp //changed in 2.0.0
    { "NpcHouseList", &Smmh::Land::VersionedOffsets::NpcHouseList },                                    //don't fit //handled by save_npc_house_list.hpp //changed in 2.0.0
    { "Shop", &Smmh::Land::VersionedOffsets::Shop },                                                    //don't fit // all shops changed size; exception: ShopKabu; added ShopGardening, ShopGallery, ShopCommune //changed in 1.2.0; 1.5.0; 1.6.0; 1.7.0; 1.9.0; 2.0.0
    { "Museum", &Smmh::Land::VersionedOffsets::Museum },                                                //fits
    { "VisitorNpc", &Smmh::Land::VersionedOffsets::VisitorNpc },                                        //fits
    { "SnowManFamily", &Smmh::Land::VersionedOffsets::SnowManFamily },                                  //fits
    { "Fg", &Smmh::Land::VersionedOffsets::Fg },                                                        //fits
    { "ItemMarketingRoute", &Smmh::Land::VersionedOffsets::ItemMarketingRoute },                        //fits
    { "VillageMelody", &Smmh::Land::VersionedOffsets::VillageMelody },                                  //fits
    { "Office", &Smmh::Land::VersionedOffsets::Office },                                                //fits
    { "BulletinBoard", &Smmh::Land::VersionedOffsets::BulletinBoard },                                  //fits
    { "RegionLanguage", &Smmh::Land::VersionedOffsets::RegionLanguage },                                //fits
    { "CalendarEventRegion", &Smmh::Land::VersionedOffsets::CalendarEventRegion },                      //fits
    { "CampSite", &Smmh::Land::VersionedOffsets::CampSite },                                            //fits
    { "NpcCamp", &Smmh::Land::VersionedOffsets::NpcCamp },                                              //fits
    { "AirportThemeColor", &Smmh::Land::VersionedOffsets::AirportThemeColor },                          //fits
    { "RumorFavorite", &Smmh::Land::VersionedOffsets::RumorFavorite },                                  //fits
    { "PublicWorksLoan", &Smmh::Land::VersionedOffsets::PublicWorksLoan },                              //fits
    { "PublicWorksName", &Smmh::Land::VersionedOffsets::PublicWorksName },                              //fits
    { "VillageScore", &Smmh::Land::VersionedOffsets::VillageScore },                                    //fits
    /*{ "NetLandProfile", &Smmh::Land::VersionedOffsets::NetLandProfile },*/                            //fits (after 1.4.0 aka dream update) //dont copy this
    { "SettlerQuest", &Smmh::Land::VersionedOffsets::SettlerQuest },                                    //introduced in 1.4.0 for some bizarro reason?
};

constexpr FieldPlayerInfo personal_fields_to_copy[] = {
    { "_18fdb93f", &Smmh::Player::VersionedOffsets::_18fdb93f },                                        //s8
    { "LookPack", &Smmh::Player::VersionedOffsets::LookPack },
    { "PlayerId", &Smmh::Player::VersionedOffsets::PlayerId },
    { "EventFlag", &Smmh::Player::VersionedOffsets::EventFlag },
    { "LifeSupport", &Smmh::Player::VersionedOffsets::LifeSupport },
    { "BirthDay", &Smmh::Player::VersionedOffsets::BirthDay },
    { "PastDaysFromMade", &Smmh::Player::VersionedOffsets::PastDaysFromMade },
    // { "NetProfile", &Smmh::Player::VersionedOffsets::NetProfile },                                      //don't fit //changed in 2.0.0; size += 0x2 (+"PlannerID"), can be zero'd
    { "ProfileMain", &Smmh::Player::VersionedOffsets::ProfileMain },
    { "_5d1fcb04", &Smmh::Player::VersionedOffsets::_5d1fcb04 }, //u8
    { "LastPlayDate", &Smmh::Player::VersionedOffsets::LastPlayDate },
    { "LastBirthdayYear", &Smmh::Player::VersionedOffsets::LastBirthdayYear },
    { "BirthdayLiveDate", &Smmh::Player::VersionedOffsets::BirthdayLiveDate },
    { "BirthdayLiveMsgList", &Smmh::Player::VersionedOffsets::BirthdayLiveMsgList },
    { "GalleryItem", &Smmh::Player::VersionedOffsets::GalleryItem },
    { "GalleryLandId", &Smmh::Player::VersionedOffsets::GalleryLandId },
    { "PreviousLandId", &Smmh::Player::VersionedOffsets::PreviousLandId },                          //don't fit //introduced in 1.5.0
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
