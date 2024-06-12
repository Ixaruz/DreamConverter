#pragma once
#include <save_struct.hpp>
#include <cstring>

namespace save_npc {
    // enum class save_npc_type {
    //     none = 0,
    //     type_1, //1.4.0
    //     type_2, //1.5.0
    //     type_3 //2.0.0
    // };

    // Interface class
    class save_npc {
    public:
        virtual u8 const *to_bin() = 0;
        virtual int get_size() = 0;

        virtual void from_data(u8 *data) = 0;

        virtual std::unique_ptr<save_npc> upgrade() = 0;
        virtual std::unique_ptr<save_npc> downgrade() = 0;
    };

    class save_npc_1 : public save_npc {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_npc_1() = default;
        save_npc_1(const save_npc_1&) = default;
        save_npc_1(save_npc_1&&) = default;
        save_npc_1(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_npc> upgrade() override;
        std::unique_ptr<save_npc> downgrade() override;
    private:
        static const int m_size = 0x1D6D48;
        u8 m_buffer[m_size];
    };

    class save_npc_2 : public save_npc {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_npc_2() = default;
        save_npc_2(const save_npc_2&) = default;
        save_npc_2(save_npc_2&&) = default;
        save_npc_2(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_npc> upgrade() override;
        std::unique_ptr<save_npc> downgrade() override;
    private:
        static const int m_size = 0x1E2148;
        u8 m_buffer[m_size];
    };

    class save_npc_3 : public save_npc {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_npc_3() = default;
        save_npc_3(const save_npc_3&) = default;
        save_npc_3(save_npc_3&&) = default;
        save_npc_3(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_npc> upgrade() override;
        std::unique_ptr<save_npc> downgrade() override;
    private:
        static const int m_size = 0x1E3388;
        u8 m_buffer[m_size];
    };

    std::unique_ptr<save_npc> get_save_npc(u8 *data, u16 revision_in, u16 revision_out);
}
