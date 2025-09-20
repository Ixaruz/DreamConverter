#pragma once
#include "save_struct.hpp"

#include <cstring>


namespace save_npc_house {

    // enum class save_npc_house_type{
    //     none = 0,
    //     type_1,
    //     type_2
    // };

    // Interface class
    class save_npc_house {
    public:
        virtual u8 const *to_bin() = 0;
        virtual int get_size() = 0;

        virtual void from_data(u8 *data) = 0;

        virtual std::unique_ptr<save_npc_house> upgrade() = 0;
        virtual std::unique_ptr<save_npc_house> downgrade() = 0;
    };

    class save_npc_house_1 : public save_npc_house {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_npc_house_1() = default;
        save_npc_house_1(const save_npc_house_1&) = default;
        save_npc_house_1(save_npc_house_1&&) = default;
        save_npc_house_1(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_npc_house> upgrade() override;
        std::unique_ptr<save_npc_house> downgrade() override;
    private:
        static const int m_size = 0x1D4;
        u8 m_buffer[m_size];
    };

    class save_npc_house_2 : public save_npc_house {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_npc_house_2() = default;
        save_npc_house_2(const save_npc_house_2&) = default;
        save_npc_house_2(save_npc_house_2&&) = default;
        save_npc_house_2(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_npc_house> upgrade() override;
        std::unique_ptr<save_npc_house> downgrade() override;
    private:
        static const int m_size = 0x12E8;
        u8 m_buffer[m_size];
    };

    std::unique_ptr<save_npc_house> get_save_npc_house(u8 *data, u16 revision_in, u16 revision_out);

    std::vector<std::unique_ptr<save_npc_house>> get_save_npc_house_list(u8 *data, u16 revision_in, u16 revision_out);
};
