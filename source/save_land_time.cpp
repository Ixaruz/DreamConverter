#include <save_land_time.hpp>

namespace save_land_time {
    save_land_time_1::save_land_time_1(void *data) {
        LastGrowUpTime =*(u64 *)(data);
        CreateDate =*(u32 *)((u8 *)data + 0x8);
        SummerTimeFlag =*(u8 *)((u8 *)data + 0xC);
        InitializeFlag =*(u8 *)((u8 *)data + 0xD);
        /*alignment 8*/
        memcpy(ClockSnapshot, (u8 *)data + 0x10, 0xD0);
    }

    u8 * save_land_time_1::to_bin(){
        u8 *buffer = new u8[size]{0};
        *(u64 *)(buffer) = LastGrowUpTime;
        *(u32 *)(buffer + 0x8) = CreateDate;
        *(u8 *)(buffer + 0xC) = SummerTimeFlag;
        *(u8 *)(buffer + 0xD) = InitializeFlag;
        memcpy(buffer + 0x10, ClockSnapshot, 0xD0);
        return buffer;
    }

    save_land_time_2::save_land_time_2(void *data){
        LastGrowUpTime =*(u64 *)(data);
        _a8cbefd7 = *(u64 *)((u8 *)data + 0x8);
        CreateDate =*(u32 *)((u8 *)data + 0x10);
        SummerTimeFlag =*(u8 *)((u8 *)data + 0x14);
        InitializeFlag =*(u8 *)((u8 *)data + 0x15);
        /*alignment 8*/
        memcpy(ClockSnapshot, (u8 *)data + 0x18, 0xD0);
    }

    u8 * save_land_time_2::to_bin() {
        u8 *buffer = new u8[size]{0};
        *(u64 *)(buffer) = LastGrowUpTime;
        *(u64 *)(buffer + 0x8) = _a8cbefd7;
        *(u32 *)(buffer + 0x10) = CreateDate;
        *(u8 *)(buffer + 0x14) = SummerTimeFlag;
        *(u8 *)(buffer + 0x15) = InitializeFlag;
        memcpy(buffer + 0x10, ClockSnapshot, 0xD0);
        return buffer;
    }

    save_land_time_1 *save_land_time_2::downgrade() {
        return new save_land_time_1(LastGrowUpTime, CreateDate, SummerTimeFlag, InitializeFlag, ClockSnapshot);
    }

    save_land_time_2 *upgrade(save_land_time_1 save_land_time) {
        return new save_land_time_2(save_land_time.LastGrowUpTime, save_land_time.LastGrowUpTime, save_land_time.CreateDate, save_land_time.SummerTimeFlag, save_land_time.InitializeFlag, save_land_time.ClockSnapshot);
    }

    std::unique_ptr<save_land_time_1 *> get_save_land_time(void *data, u16 revision_in, u16 revision_out, save_land_time_type &type) {
        switch(revision_out) {
            case 0 ... 21:
            {
                type = save_land_time_type::type_1;
                switch(revision_in) {
                    case 0 ... 21:
                        return std::make_unique<save_land_time_1 *>(new save_land_time_1(data));
                    case 22 ... 28:
                        return std::make_unique<save_land_time_1 *>(save_land_time_2(data).downgrade());
                    default: 
                        break;
                }
            }
            case 22 ... 28:
            {
                type = save_land_time_type::type_2;
                switch(revision_in) {
                    case 0 ... 21:
                        return std::make_unique<save_land_time_1 *>(upgrade(save_land_time_1(data)));
                    case 22 ... 28:
                        return std::make_unique<save_land_time_1 *>(new save_land_time_2(data));
                    default: 
                        break;
                }
            }
            default:
                type = save_land_time_type::none;
                return std::make_unique<save_land_time_1 *>(nullptr);
        }
    }
}