#include <save_land_time.hpp>

namespace save_land_time
{
    std::vector<u16> revisions =
    {
        21, //1.11.0 (revision before upgrade)
        22 //2.0.0
    };

    static std::map<u16, std::function<std::unique_ptr<save_land_time>(u8*)>> constructors =
    {
        {21, [](u8* data){ return std::make_unique<save_land_time_1>(data); }},
        {22, [](u8* data){ return std::make_unique<save_land_time_2>(data); }}
    };


    u8 const *save_land_time_1::to_bin()
    {
        u8 *buffer = new u8[m_size]{0};
        *(u64 *)(buffer) = m_LastGrowUpTime;
        *(u32 *)(buffer + 0x8) = m_CreateDate;
        *(u8 *)(buffer + 0xC) = m_SummerTimeFlag;
        *(u8 *)(buffer + 0xD) = m_InitializeFlag;
        /*alignment 8*/
        memcpy(buffer + 0x10, m_ClockSnapshot, sizeof(m_ClockSnapshot));
        return buffer;
    }

    u8 const *save_land_time_2::to_bin()
    {
        u8 *buffer = new u8[m_size]{0};
        *(u64 *)(buffer) = m_LastGrowUpTime;
        *(u64 *)(buffer + 0x8) = m_a8cbefd7;
        *(u32 *)(buffer + 0x10) = m_CreateDate;
        *(u8 *)(buffer + 0x14) = m_SummerTimeFlag;
        *(u8 *)(buffer + 0x15) = m_InitializeFlag;
        /*alignment 8*/
        memcpy(buffer + 0x18, m_ClockSnapshot, sizeof(m_ClockSnapshot));
        return buffer;
    }

    int save_land_time_1::get_size() { return m_size; }
    int save_land_time_2::get_size() { return m_size; }

    u64 save_land_time_1::get_LastGrowUpTime() { return m_LastGrowUpTime; }
    u32 save_land_time_1::get_CreateDate() { return m_CreateDate; }
    u8  save_land_time_1::get_SummerTimeFlag() { return m_SummerTimeFlag; }
    u8  save_land_time_1::get_InitializeFlag() { return m_InitializeFlag; }
    u8 const *save_land_time_1::get_ClockSnapshot() { return m_ClockSnapshot; }

    u64 save_land_time_2::get_LastGrowUpTime() { return m_LastGrowUpTime; }
    u32 save_land_time_2::get_CreateDate() { return m_CreateDate; }
    u8  save_land_time_2::get_SummerTimeFlag() { return m_SummerTimeFlag; }
    u8  save_land_time_2::get_InitializeFlag() { return m_InitializeFlag; }
    u8 const *save_land_time_2::get_ClockSnapshot() { return m_ClockSnapshot; }

    void save_land_time_1::from_data(u8 *data)
    {
        memcpy(&m_LastGrowUpTime, (u8 *)data, sizeof(m_LastGrowUpTime));
        memcpy(&m_CreateDate, (u8 *)data + 0x8, sizeof(m_CreateDate));
        memcpy(&m_SummerTimeFlag, (u8 *)data + 0xC, sizeof(m_SummerTimeFlag));
        memcpy(&m_InitializeFlag, (u8 *)data + 0xD, sizeof(m_InitializeFlag));
        /*alignment 8*/
        memcpy(m_ClockSnapshot, (u8 *)data + 0x10, sizeof(m_ClockSnapshot));
    }

    void save_land_time_2::from_data(u8 *data)
    {
        memcpy(&m_LastGrowUpTime, (u8 *)data, sizeof(m_LastGrowUpTime));
        memcpy(&m_a8cbefd7, (u8 *)data + 0x8, sizeof(m_a8cbefd7));
        memcpy(&m_CreateDate, (u8 *)data + 0x10, sizeof(m_CreateDate));
        memcpy(&m_SummerTimeFlag, (u8 *)data + 0x14, sizeof(m_SummerTimeFlag));
        memcpy(&m_InitializeFlag, (u8 *)data + 0x15, sizeof(m_InitializeFlag));
        /*alignment 8*/
        memcpy(m_ClockSnapshot, (u8 *)data + 0x18, sizeof(m_ClockSnapshot));
    }

    save_land_time_1::save_land_time_1(u8 *data) { this->from_data(data); }
    save_land_time_2::save_land_time_2(u8 *data) { this->from_data(data); }

    std::unique_ptr<save_land_time> save_land_time_1::downgrade()
    {
        return std::make_unique<save_land_time_1>(*(this));
    }

    std::unique_ptr<save_land_time> save_land_time_2::downgrade() {
        save_land_time_1 *res = new save_land_time_1();
        u8 *buffer = new u8[res->get_size()]{0};
        *(u64 *)(buffer) = m_LastGrowUpTime;
        *(u32 *)(buffer + 0x8) = m_CreateDate;
        *(u8 *)(buffer + 0xC) = m_SummerTimeFlag;
        *(u8 *)(buffer + 0xD) = m_InitializeFlag;
        /*alignment 8*/
        memcpy(buffer + 0x10, m_ClockSnapshot, sizeof(m_ClockSnapshot));
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_land_time_1>(*(res));
    }

    std::unique_ptr<save_land_time> save_land_time_1::upgrade() {
        save_land_time_2 *res = new save_land_time_2();
        u8 *buffer = new u8[res->get_size()]{0};
        *(u64 *)(buffer) = m_LastGrowUpTime;
        *(u64 *)(buffer + 0x8) = 0;
        *(u32 *)(buffer + 0x10) = m_CreateDate;
        *(u8 *)(buffer + 0x14) = m_SummerTimeFlag;
        *(u8 *)(buffer + 0x15) = m_InitializeFlag;
        /*alignment 8*/
        memcpy(buffer + 0x18, m_ClockSnapshot, sizeof(m_ClockSnapshot));
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_land_time_2>(*(res));
    }

    std::unique_ptr<save_land_time> save_land_time_2::upgrade()
    {
        return std::make_unique<save_land_time_2>(*(this));
    }

    std::unique_ptr<save_land_time> get_save_land_time(u8 *data, u16 revision_in, u16 revision_out)
    {
        return save_struct::get_save_struct<save_land_time>(constructors,
                                                            revisions,
                                                            data,
                                                            revision_in,
                                                            revision_out);
    }
}
