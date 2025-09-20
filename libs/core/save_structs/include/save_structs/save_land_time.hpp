#pragma once
#include "save_struct.hpp"

#include <cstring>

namespace save_land_time {

    // enum class save_land_time_type{
    //     none = 0,
    //     type_1,
    //     type_2
    // };

    // Interface class
    class save_land_time {
    public:
        virtual u8 const *to_bin() = 0;
        virtual int get_size() = 0;

        virtual u64 get_LastGrowUpTime() = 0;
        virtual u32 get_CreateDate() = 0;
        virtual u8  get_SummerTimeFlag() = 0;
        virtual u8  get_InitializeFlag() = 0;
        virtual u8  const *get_ClockSnapshot() = 0;

        virtual void from_data(u8 *data) = 0;

        virtual std::unique_ptr<save_land_time> upgrade() = 0;
        virtual std::unique_ptr<save_land_time> downgrade() = 0;
    };

    class save_land_time_1 : public save_land_time {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        u64 get_LastGrowUpTime() override;
        u32 get_CreateDate() override;
        u8  get_SummerTimeFlag() override;
        u8  get_InitializeFlag() override;
        u8  const *get_ClockSnapshot() override;

        save_land_time_1() = default;
        save_land_time_1(const save_land_time_1&) = default;
        save_land_time_1(save_land_time_1&&) = default;
        save_land_time_1(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_land_time> upgrade() override;
        std::unique_ptr<save_land_time> downgrade() override;
    private:
        static const int m_size = 0xE0;
        u64 m_LastGrowUpTime;
        u32 m_CreateDate;
        u8 m_SummerTimeFlag;
        u8 m_InitializeFlag;
        u8 m_ClockSnapshot[0xD0];
    };

    class save_land_time_2 : public save_land_time {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        u64 get_LastGrowUpTime() override;
        u32 get_CreateDate() override;
        u8  get_SummerTimeFlag() override;
        u8  get_InitializeFlag() override;
        u8  const *get_ClockSnapshot() override;

        save_land_time_2() = default;
        save_land_time_2(const save_land_time_2&) = default;
        save_land_time_2(save_land_time_2&&) = default;
        save_land_time_2(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_land_time> upgrade() override;
        std::unique_ptr<save_land_time> downgrade() override;
    private:
        static const int m_size = 0xE8;
        u64 m_LastGrowUpTime;
        u32 m_CreateDate;
        u8 m_SummerTimeFlag;
        u8 m_InitializeFlag;
        u8 m_ClockSnapshot[0xD0];
        u64 m_a8cbefd7;
    };

    std::unique_ptr<save_land_time> get_save_land_time(u8 *data, u16 revision_in, u16 revision_out);
};
