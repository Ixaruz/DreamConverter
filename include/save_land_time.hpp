#pragma once
#include <types.hpp>
#include <cstring>
#include <memory>

namespace save_land_time {
    
    enum class save_land_time_type{
        none = 0,
        type_1,
        type_2
    };

    class save_land_time_1 {
    protected:
        static const int size = 0xE0;

        save_land_time_1() {}
    public:
        static int get_size() {return size;}

        u64 LastGrowUpTime;
        u32 CreateDate;
        u8 SummerTimeFlag;
        u8 InitializeFlag;
        u8 ClockSnapshot[0xD0];

        save_land_time_1(void *data);
        
        save_land_time_1(u64 _LastGrowUpTime, u32 _CreateDate, u8 _SummerTimeFlag, u8 _InitializeFlag, u8 *_ClockSnapshot) : 
        LastGrowUpTime(_LastGrowUpTime), CreateDate(_CreateDate), SummerTimeFlag(_SummerTimeFlag), InitializeFlag(_InitializeFlag)
        {memcpy(ClockSnapshot, _ClockSnapshot, 0xD0);}
        
        virtual u8 * to_bin();
    };

    class save_land_time_2 : public save_land_time_1 {
    protected:
        static const int size = 0xE8;
    public:
        static int get_size() {return size;}

        u64 _a8cbefd7;

        save_land_time_2(void *data);

        save_land_time_2(u64 _LastGrowUpTime, u64 ___a8cbefd7, u32 _CreateDate, u8 _SummerTimeFlag, u8 _InitializeFlag, u8 *_ClockSnapshot) : 
        save_land_time_1(_LastGrowUpTime, _CreateDate, _SummerTimeFlag, _InitializeFlag, _ClockSnapshot), _a8cbefd7(___a8cbefd7)
        {}

        u8 * to_bin() override;

        save_land_time_1 *downgrade();
    };

    save_land_time_2 *upgrade(save_land_time_1 save_land_time);

    std::unique_ptr<save_land_time_1 *> get_save_land_time(void *data, u16 revision_in, u16 revision_out, save_land_time_type &type);
};