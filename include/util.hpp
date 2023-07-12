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
#include <types.hpp>

using namespace std;
namespace fs = std::filesystem;

const s32 DreamHeaderSize = 0x830;
const s32 SaveHeaderSize = 0x110;

const u32 mainSize = 0x547520 - SaveHeaderSize; //changed in 2.0.0 // GSaveLandOther - Header
const u32 GSavePlayerVillagerAccountOffset = 0x1E34C0 - SaveHeaderSize; //changed in 2.0.0
const u32 GSavePlayerVillagerAccountSize = 0x48;
const u32 GAccountTableOffset = 0x10;
//extern const u32 GAccountTableSize = GAccountTableOffset + (0x8 * GSavePlayerVillagerAccountSize);
const u32 DreamIDOffset = 0x545F50; //changed in 2.0.0
const u32 DreamInfoSize = 0x50;


const u32 playerSize = 0x36A50 - SaveHeaderSize; //changed in 1.10.0 // GSaveLandOther - Header
const u32 playersOffset = 0x7B658; //changed in 1.9.0 //alternatively in the player pointer [[[[main+XXXXXX]+10]+140]+08] you can add 0x8 to 0x140 for each additional player

//taken from NHSE
//*personal.dat*//
const u32 PersonalID = 0xAFA8; 
const u32 EventFlagsPlayerOffset = 0xAFE0;
const u32 ItemCollectBitOffset = 0xA058;
const u32 ItemRemakeCollectBitOffset = 0xA7AC;
const u32 RecipesOffset = 0x24afc + 0x10; //Bank + 0x10
const u32 StorageSizeOffset = playerSize + SaveHeaderSize + 0x18C + (8 * 5000); //absolute file offset //changed in 1.7.0 0x4081C
const u32 Pocket1SizeOffset = playerSize + SaveHeaderSize + 0x10 + (8 * 20); //absolute file offset //changed in 1.7.0 0x36B00
const u32 SpecialityFruitOffsetPersonal = 0x3540C - 0x110;
const u32 ExpandBaggageOffset = 0x36BD8;

//*main.dat*//
const u32 houseSize = 0x28A28; //changed in 2.0.0
const u32 EventFlagOffset = 0x22ebf0; //changed in 2.0.0 //EventFlagLand
const u32 houseLvlOffset = 0x30a6bc; //changed in 2.0.0 //PlayerHouseList
const u32 SaveFgOffset = 0x462278; //changed in 2.0.0 //SaveFg
const u32 SpecialityFruitOffset = 0x900; //SpecialityFruit

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