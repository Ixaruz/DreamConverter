#pragma once
#include "file_hash_info.hpp"

const std::string FN_MAIN = "main.dat";
const std::string FN_PERSONAL = "personal.dat";
const std::string FN_POSTBOX = "postbox.dat";
const std::string FN_PHOTO = "photo_studio_island.dat";
const std::string FN_PROFILE = "profile.dat";
const std::string FN_WHEREAREN = "wherearen.dat";

const int REV_100_MAIN = 0xAC0938;
const int REV_100_PERSONAL = 0x6BC50;
const int REV_100_POSTBOX = 0xB44580;
const int REV_100_PHOTO = 0x263B4;
const int REV_100_PROFILE = 0x69508;

static file_hash_info REV_100 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_100_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000108, 0x1D6D4C),
        new file_hash_region(0x1D6E58, 0x323384),
        new file_hash_region(0x4FA2E8, 0x035AC4),
        new file_hash_region(0x52FDB0, 0x03607C),
        new file_hash_region(0x565F38, 0x035AC4),
        new file_hash_region(0x59BA00, 0x03607C),
        new file_hash_region(0x5D1B88, 0x035AC4),
        new file_hash_region(0x607650, 0x03607C),
        new file_hash_region(0x63D7D8, 0x035AC4),
        new file_hash_region(0x6732A0, 0x03607C),
        new file_hash_region(0x6A9428, 0x035AC4),
        new file_hash_region(0x6DEEF0, 0x03607C),
        new file_hash_region(0x715078, 0x035AC4),
        new file_hash_region(0x74AB40, 0x03607C),
        new file_hash_region(0x780CC8, 0x035AC4),
        new file_hash_region(0x7B6790, 0x03607C),
        new file_hash_region(0x7EC918, 0x035AC4),
        new file_hash_region(0x8223E0, 0x03607C),
        new file_hash_region(0x858460, 0x2684D4)
    }),
    new file_hash_details(FN_PERSONAL, REV_100_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00108, 0x35AC4),
        new file_hash_region(0x35BD0, 0x3607C)
    }),
    new file_hash_details(FN_POSTBOX, REV_100_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0xB4447C)
    }),
    new file_hash_details(FN_PHOTO, REV_100_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x262B0)
    }),
    new file_hash_details(FN_PROFILE, REV_100_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x69404)
    }),
});

const int REV_110_MAIN = 0xAC2AA0;
const int REV_110_PERSONAL = 0x6BED0;
const int REV_110_POSTBOX = 0xB44590;
const int REV_110_PHOTO = 0x263C0;
const int REV_110_PROFILE = 0x69560;

static file_hash_info REV_110 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_110_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1D6D5C),
        new file_hash_region(0x1D6E70, 0x323C0C),
        new file_hash_region(0x4FAB90, 0x035AFC),
        new file_hash_region(0x530690, 0x0362BC),
        new file_hash_region(0x566A60, 0x035AFC),
        new file_hash_region(0x59C560, 0x0362BC),
        new file_hash_region(0x5D2930, 0x035AFC),
        new file_hash_region(0x608430, 0x0362BC),
        new file_hash_region(0x63E800, 0x035AFC),
        new file_hash_region(0x674300, 0x0362BC),
        new file_hash_region(0x6AA6D0, 0x035AFC),
        new file_hash_region(0x6E01D0, 0x0362BC),
        new file_hash_region(0x7165A0, 0x035AFC),
        new file_hash_region(0x74C0A0, 0x0362BC),
        new file_hash_region(0x782470, 0x035AFC),
        new file_hash_region(0x7B7F70, 0x0362BC),
        new file_hash_region(0x7EE340, 0x035AFC),
        new file_hash_region(0x823E40, 0x0362BC),
        new file_hash_region(0x85A100, 0x26899C)
    }),
    new file_hash_details(FN_PERSONAL, REV_110_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x35AFC),
        new file_hash_region(0x35C10, 0x362BC)
    }),
    new file_hash_details(FN_POSTBOX, REV_110_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0xB4448C)
    }),
    new file_hash_details(FN_PHOTO, REV_110_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x262BC)
    }),
    new file_hash_details(FN_PROFILE, REV_110_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});

const int REV_120_MAIN = 0xACECD0;
const int REV_120_PERSONAL = 0x6D6C0;
const int REV_120_POSTBOX = REV_110_POSTBOX;
const int REV_120_PHOTO = 0x2C9C0;
const int REV_120_PROFILE = REV_110_PROFILE;

static file_hash_info REV_120 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_120_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1D6D5C),
        new file_hash_region(0x1D6E70, 0x323EBC),
        new file_hash_region(0x4FAE40, 0x035D2C),
        new file_hash_region(0x530B70, 0x03787C),
        new file_hash_region(0x568500, 0x035D2C),
        new file_hash_region(0x59E230, 0x03787C),
        new file_hash_region(0x5D5BC0, 0x035D2C),
        new file_hash_region(0x60B8F0, 0x03787C),
        new file_hash_region(0x643280, 0x035D2C),
        new file_hash_region(0x678FB0, 0x03787C),
        new file_hash_region(0x6B0940, 0x035D2C),
        new file_hash_region(0x6E6670, 0x03787C),
        new file_hash_region(0x71E000, 0x035D2C),
        new file_hash_region(0x753D30, 0x03787C),
        new file_hash_region(0x78B6C0, 0x035D2C),
        new file_hash_region(0x7C13F0, 0x03787C),
        new file_hash_region(0x7F8D80, 0x035D2C),
        new file_hash_region(0x82EAB0, 0x03787C),
        new file_hash_region(0x866330, 0x26899C)
    }),
    new file_hash_details(FN_PERSONAL, REV_120_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x35D2C),
        new file_hash_region(0x35E40, 0x3787C)
    }),
    new file_hash_details(FN_POSTBOX, REV_120_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0xB4448C)
    }),
    new file_hash_details(FN_PHOTO, REV_120_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x2C8BC)
    }),
    new file_hash_details(FN_PROFILE, REV_120_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});

const int REV_130_MAIN = 0xACED80;
const int REV_130_PERSONAL = 0x6D6D0;
const int REV_130_POSTBOX = REV_110_POSTBOX;
const int REV_130_PHOTO = REV_120_PHOTO;
const int REV_130_PROFILE = REV_110_PROFILE;

static file_hash_info REV_130 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_130_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1D6D5C),
        new file_hash_region(0x1D6E70, 0x323EEC),
        new file_hash_region(0x4FAE70, 0x035D2C),
        new file_hash_region(0x530BA0, 0x03788C),
        new file_hash_region(0x568540, 0x035D2C),
        new file_hash_region(0x59E270, 0x03788C),
        new file_hash_region(0x5D5c10, 0x035D2C),
        new file_hash_region(0x60B940, 0x03788C),
        new file_hash_region(0x6432E0, 0x035D2C),
        new file_hash_region(0x679010, 0x03788C),
        new file_hash_region(0x6B09B0, 0x035D2C),
        new file_hash_region(0x6E66E0, 0x03788C),
        new file_hash_region(0x71E080, 0x035D2C),
        new file_hash_region(0x753DB0, 0x03788C),
        new file_hash_region(0x78B750, 0x035D2C),
        new file_hash_region(0x7C1480, 0x03788C),
        new file_hash_region(0x7F8E20, 0x035D2C),
        new file_hash_region(0x82EB50, 0x03788C),
        new file_hash_region(0x8663E0, 0x26899C)
    }),
    new file_hash_details(FN_PERSONAL, REV_130_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x35D2C),
        new file_hash_region(0x35E40, 0x3788C)
    }),
    new file_hash_details(FN_POSTBOX, REV_130_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0xB4448C)
    }),
    new file_hash_details(FN_PHOTO, REV_130_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x2C8BC)
    }),
    new file_hash_details(FN_PROFILE, REV_130_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});

const int REV_140_MAIN = 0xB05790;
const int REV_140_PERSONAL = 0x74420;
const int REV_140_POSTBOX = REV_110_POSTBOX;
const int REV_140_PHOTO = REV_120_PHOTO;
const int REV_140_PROFILE = REV_110_PROFILE;

static file_hash_info REV_140 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_140_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1d6d5c),
        new file_hash_region(0x1d6e70, 0x323f2c),
        new file_hash_region(0x4faeb0, 0x035d2c),
        new file_hash_region(0x530be0, 0x03e5dc),
        new file_hash_region(0x56f2d0, 0x035d2c),
        new file_hash_region(0x5a5000, 0x03e5dc),
        new file_hash_region(0x5e36f0, 0x035d2c),
        new file_hash_region(0x619420, 0x03e5dc),
        new file_hash_region(0x657b10, 0x035d2c),
        new file_hash_region(0x68d840, 0x03e5dc),
        new file_hash_region(0x6cbf30, 0x035d2c),
        new file_hash_region(0x701c60, 0x03e5dc),
        new file_hash_region(0x740350, 0x035d2c),
        new file_hash_region(0x776080, 0x03e5dc),
        new file_hash_region(0x7b4770, 0x035d2c),
        new file_hash_region(0x7ea4a0, 0x03e5dc),
        new file_hash_region(0x828b90, 0x035d2c),
        new file_hash_region(0x85e8c0, 0x03e5dc),
        new file_hash_region(0x89cea0, 0x2688ec)
    }),
    new file_hash_details(FN_PERSONAL, REV_140_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x35D2C),
        new file_hash_region(0x35E40, 0x3E5DC)
    }),
    new file_hash_details(FN_POSTBOX, REV_140_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0xB4448C)
    }),
    new file_hash_details(FN_PHOTO, REV_140_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x2C8BC)
    }),
    new file_hash_details(FN_PROFILE, REV_140_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});

const int REV_150_MAIN = 0xB20750;
const int REV_150_PERSONAL = 0x76390;
const int REV_150_POSTBOX = REV_110_POSTBOX;
const int REV_150_PHOTO = REV_120_PHOTO;
const int REV_150_PROFILE = REV_110_PROFILE;

static file_hash_info REV_150 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_150_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1e215c),
        new file_hash_region(0x1e2270, 0x323f6c),
        new file_hash_region(0x5062f0, 0x03693c),
        new file_hash_region(0x53cc30, 0x03f93c),
        new file_hash_region(0x57c680, 0x03693c),
        new file_hash_region(0x5b2fc0, 0x03f93c),
        new file_hash_region(0x5f2a10, 0x03693c),
        new file_hash_region(0x629350, 0x03f93c),
        new file_hash_region(0x668da0, 0x03693c),
        new file_hash_region(0x69f6e0, 0x03f93c),
        new file_hash_region(0x6df130, 0x03693c),
        new file_hash_region(0x715a70, 0x03f93c),
        new file_hash_region(0x7554c0, 0x03693c),
        new file_hash_region(0x78be00, 0x03f93c),
        new file_hash_region(0x7cb850, 0x03693c),
        new file_hash_region(0x802190, 0x03f93c),
        new file_hash_region(0x841be0, 0x03693c),
        new file_hash_region(0x878520, 0x03f93c),
        new file_hash_region(0x8b7e60, 0x2688ec)
    }),
    new file_hash_details(FN_PERSONAL, REV_150_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x3693c),
        new file_hash_region(0x36a50, 0x3f93c)
    }),
    new file_hash_details(FN_POSTBOX, REV_150_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0xB4448C)
    }),
    new file_hash_details(FN_PHOTO, REV_150_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x2C8BC)
    }),
    new file_hash_details(FN_PROFILE, REV_150_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});

const int REV_160_MAIN = 0xB258E0;
const int REV_160_PERSONAL = 0x76CF0;
const int REV_160_POSTBOX = REV_110_POSTBOX;
const int REV_160_PHOTO = REV_120_PHOTO;
const int REV_160_PROFILE = REV_110_PROFILE;

static file_hash_info REV_160 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_160_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1e215c),
        new file_hash_region(0x1e2270, 0x32403c),
        new file_hash_region(0x5063c0, 0x03693c),
        new file_hash_region(0x53cd00, 0x04029c),
        new file_hash_region(0x57d0b0, 0x03693c),
        new file_hash_region(0x5b39f0, 0x04029c),
        new file_hash_region(0x5f3da0, 0x03693c),
        new file_hash_region(0x62a6e0, 0x04029c),
        new file_hash_region(0x66aa90, 0x03693c),
        new file_hash_region(0x6a13d0, 0x04029c),
        new file_hash_region(0x6e1780, 0x03693c),
        new file_hash_region(0x7180c0, 0x04029c),
        new file_hash_region(0x758470, 0x03693c),
        new file_hash_region(0x78edb0, 0x04029c),
        new file_hash_region(0x7cf160, 0x03693c),
        new file_hash_region(0x805aa0, 0x04029c),
        new file_hash_region(0x845e50, 0x03693c),
        new file_hash_region(0x87c790, 0x04029c),
        new file_hash_region(0x8bca30, 0x268eac)
    }),
    new file_hash_details(FN_PERSONAL, REV_160_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x3693c),
        new file_hash_region(0x36a50, 0x4029c)
    }),
    new file_hash_details(FN_POSTBOX, REV_160_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0xB4448C)
    }),
    new file_hash_details(FN_PHOTO, REV_160_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x2C8BC)
    }),
    new file_hash_details(FN_PROFILE, REV_160_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});

const int REV_170_MAIN = 0x849C30; // reduced size
const int REV_170_PERSONAL = 0x64140; // reduced size
const int REV_170_POSTBOX = 0x47430; // reduced size
const int REV_170_PHOTO = REV_120_PHOTO;
const int REV_170_PROFILE = REV_110_PROFILE;

static file_hash_info REV_170 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_170_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1e215c),
        new file_hash_region(0x1e2270, 0x3221fc),
        new file_hash_region(0x504580, 0x03693c),
        new file_hash_region(0x53aec0, 0x02d6ec),
        new file_hash_region(0x5686c0, 0x03693c),
        new file_hash_region(0x59f000, 0x02d6ec),
        new file_hash_region(0x5cc800, 0x03693c),
        new file_hash_region(0x603140, 0x02d6ec),
        new file_hash_region(0x630940, 0x03693c),
        new file_hash_region(0x667280, 0x02d6ec),
        new file_hash_region(0x694a80, 0x03693c),
        new file_hash_region(0x6cb3c0, 0x02d6ec),
        new file_hash_region(0x6f8bc0, 0x03693c),
        new file_hash_region(0x72f500, 0x02d6ec),
        new file_hash_region(0x75cd00, 0x03693c),
        new file_hash_region(0x793640, 0x02d6ec),
        new file_hash_region(0x7c0e40, 0x03693c),
        new file_hash_region(0x7f7780, 0x02d6ec),
        new file_hash_region(0x824e70, 0x024dbc),
    }),
    new file_hash_details(FN_PERSONAL, REV_170_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x3693c),
        new file_hash_region(0x36a50, 0x2d6ec),
    }),
    new file_hash_details(FN_POSTBOX, REV_170_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x4732c)
    }),
    new file_hash_details(FN_PHOTO, REV_170_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x2C8BC)
    }),
    new file_hash_details(FN_PROFILE, REV_170_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});


const int REV_180_MAIN = REV_170_MAIN;
const int REV_180_PERSONAL = REV_170_PERSONAL;
const int REV_180_POSTBOX = REV_170_POSTBOX;
const int REV_180_PHOTO = REV_120_PHOTO;
const int REV_180_PROFILE = REV_110_PROFILE;

static file_hash_info REV_180 = REV_170;


const int REV_190_MAIN = 0x86D560;
const int REV_190_PERSONAL = 0x64160;
const int REV_190_POSTBOX = REV_170_POSTBOX;
const int REV_190_PHOTO = REV_120_PHOTO;
const int REV_190_PROFILE = REV_110_PROFILE;

static file_hash_info REV_190 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_190_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1e215c),
        new file_hash_region(0x1e2270, 0x34582c),
        new file_hash_region(0x527bb0, 0x03693c),
        new file_hash_region(0x55e4f0, 0x02d70c),
        new file_hash_region(0x58bd10, 0x03693c),
        new file_hash_region(0x5c2650, 0x02d70c),
        new file_hash_region(0x5efe70, 0x03693c),
        new file_hash_region(0x6267b0, 0x02d70c),
        new file_hash_region(0x653fd0, 0x03693c),
        new file_hash_region(0x68a910, 0x02d70c),
        new file_hash_region(0x6b8130, 0x03693c),
        new file_hash_region(0x6eea70, 0x02d70c),
        new file_hash_region(0x71c290, 0x03693c),
        new file_hash_region(0x752bd0, 0x02d70c),
        new file_hash_region(0x7803f0, 0x03693c),
        new file_hash_region(0x7b6d30, 0x02d70c),
        new file_hash_region(0x7e4550, 0x03693c),
        new file_hash_region(0x81ae90, 0x02d70c),
        new file_hash_region(0x8485a0, 0x024fbc),
    }),
    new file_hash_details(FN_PERSONAL, REV_190_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x3693c),
        new file_hash_region(0x36a50, 0x2d70c),
    }),
    new file_hash_details(FN_POSTBOX, REV_190_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x4732c)
    }),
    new file_hash_details(FN_PHOTO, REV_190_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x2C8BC)
    }),
    new file_hash_details(FN_PROFILE, REV_190_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});

const int REV_1100_MAIN = 0x86D570;
const int REV_1100_PERSONAL = REV_190_PERSONAL;
const int REV_1100_POSTBOX = REV_170_POSTBOX;
const int REV_1100_PHOTO = 0x2C9D0;
const int REV_1100_PROFILE = REV_110_PROFILE;

static file_hash_info REV_1100 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_1100_MAIN,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1e216c),
        new file_hash_region(0x1e2280, 0x34582c),
        new file_hash_region(0x527bc0, 0x03693c),
        new file_hash_region(0x55e500, 0x02d70c),
        new file_hash_region(0x58bd20, 0x03693c),
        new file_hash_region(0x5c2660, 0x02d70c),
        new file_hash_region(0x5efe80, 0x03693c),
        new file_hash_region(0x6267c0, 0x02d70c),
        new file_hash_region(0x653fe0, 0x03693c),
        new file_hash_region(0x68a920, 0x02d70c),
        new file_hash_region(0x6b8140, 0x03693c),
        new file_hash_region(0x6eea80, 0x02d70c),
        new file_hash_region(0x71c2a0, 0x03693c),
        new file_hash_region(0x752be0, 0x02d70c),
        new file_hash_region(0x780400, 0x03693c),
        new file_hash_region(0x7b6d40, 0x02d70c),
        new file_hash_region(0x7e4560, 0x03693c),
        new file_hash_region(0x81aea0, 0x02d70c),
        new file_hash_region(0x8485b0, 0x024fbc),
    }),
    new file_hash_details(FN_PERSONAL, REV_1100_PERSONAL,std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x3693c),
        new file_hash_region(0x36a50, 0x2d70c),
    }),
    new file_hash_details(FN_POSTBOX, REV_1100_POSTBOX,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x4732c)
    }),
    new file_hash_details(FN_PHOTO, REV_1100_PHOTO,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x2c8cc)
    }),
    new file_hash_details(FN_PROFILE, REV_1100_PROFILE,std::vector<file_hash_region*>
    {
        new file_hash_region(0x000100, 0x6945C)
    }),
});

const int REV_1110_MAIN = REV_1100_MAIN;
const int REV_1110_PERSONAL = REV_190_PERSONAL;
const int REV_1110_POSTBOX = REV_170_POSTBOX;
const int REV_1110_PHOTO = REV_1100_PHOTO;
const int REV_1110_PROFILE = REV_110_PROFILE;

static file_hash_info REV_1110 = REV_1100;


const u32 REV_200_MAIN = 0x8F1BB0;
const u32 REV_200_PERSONAL = 0x6A520;
const u32 REV_200_POSTBOX = 0x64140;
const u32 REV_200_PHOTO = 0x2F650;
const u32 REV_200_PROFILE = 0x69560;
const u32 REV_200_WHEREAREN = 0xB8A4E0;

static file_hash_info  REV_200 = file_hash_info (std::vector<file_hash_details*>
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

const u32 REV_300_MAIN = 0x9B0E90;
const u32 REV_300_PERSONAL = 0x74A40;
const u32 REV_300_POSTBOX = 0x64140;
const u32 REV_300_PHOTO = 0x2F650;
const u32 REV_300_PROFILE = 0x69560;
const u32 REV_300_WHEREAREN = 0xB8A4E0;

static file_hash_info  REV_300 = file_hash_info (std::vector<file_hash_details*>
{
    new file_hash_details(FN_MAIN, REV_300_MAIN, std::vector<file_hash_region*>
    {
        new file_hash_region(0x000110, 0x1e339c),
        new file_hash_region(0x1e34b0, 0x3d089c),
        new file_hash_region(0x5b3e60, 0x037acc),
        new file_hash_region(0x5eb930, 0x03ce5c),
        new file_hash_region(0x6288a0, 0x037acc),
        new file_hash_region(0x660370, 0x03ce5c),
        new file_hash_region(0x69d2e0, 0x037acc),
        new file_hash_region(0x6d4db0, 0x03ce5c),
        new file_hash_region(0x711d20, 0x037acc),
        new file_hash_region(0x7497f0, 0x03ce5c),
        new file_hash_region(0x786760, 0x037acc),
        new file_hash_region(0x7be230, 0x03ce5c),
        new file_hash_region(0x7fb1a0, 0x037acc),
        new file_hash_region(0x832c70, 0x03ce5c),
        new file_hash_region(0x86fbe0, 0x037acc),
        new file_hash_region(0x8a76b0, 0x03ce5c),
        new file_hash_region(0x8e4620, 0x037acc),
        new file_hash_region(0x91c0f0, 0x03ce5c),
        new file_hash_region(0x958f50, 0x057f3c),
    }),
    new file_hash_details(FN_PERSONAL, REV_300_PERSONAL, std::vector<file_hash_region*>
    {
        new file_hash_region(0x00110, 0x37acc),
        new file_hash_region(0x37be0, 0x3ce5c),
    }),
    new file_hash_details(FN_POSTBOX, REV_300_POSTBOX, std::vector<file_hash_region*>
    {
        new file_hash_region(0x100, 0x4732c),
    }),
    new file_hash_details(FN_PHOTO, REV_300_PHOTO, std::vector<file_hash_region*>
    {
        new file_hash_region(0x100, 0x2f54c),
    }),
    new file_hash_details(FN_PROFILE, REV_300_PROFILE, std::vector<file_hash_region*>
    {
        new file_hash_region(0x100, 0x6945c),
    }),
    new file_hash_details(FN_WHEREAREN, REV_300_WHEREAREN, std::vector<file_hash_region*>
    {
        new file_hash_region(0x100, 0xB8A3DC),
    }),
} );