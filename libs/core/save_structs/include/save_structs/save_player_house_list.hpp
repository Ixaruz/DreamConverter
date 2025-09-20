#pragma once
#include "save_struct.hpp"

#include <cstring>


namespace save_player_house {

    // Interface class
    class save_player_room {
    public:
        virtual u8 const *to_bin() = 0;
        virtual int get_size() = 0;

        virtual void from_data(u8 *data) = 0;

        virtual std::unique_ptr<save_player_room> upgrade() = 0;
        virtual std::unique_ptr<save_player_room> downgrade() = 0;
    };

    class save_player_room_1 : public save_player_room {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_player_room_1() = default;
        save_player_room_1(const save_player_room_1&) = default;
        save_player_room_1(save_player_room_1&&) = default;
        save_player_room_1(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_player_room> upgrade() override;
        std::unique_ptr<save_player_room> downgrade() override;
    private:
        static const int m_size = 0x65C8;
        u8 m_buffer[m_size];
    };

    class save_player_room_2 : public save_player_room {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_player_room_2() = default;
        save_player_room_2(const save_player_room_2&) = default;
        save_player_room_2(save_player_room_2&&) = default;
        save_player_room_2(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_player_room> upgrade() override;
        std::unique_ptr<save_player_room> downgrade() override;
    private:
        static const int m_size = 0x6C24;
        u8 m_buffer[m_size];
    };

    save_player_room_2 upgrade(save_player_room_1 player_room);

    // enum class save_player_house_type{
    //     none = 0,
    //     type_1,
    //     type_2
    // };

    // Interface class
    class save_player_house {
    public:
        virtual u8 const *to_bin() = 0;
        virtual int get_size() = 0;

        virtual void from_data(u8 *data) = 0;

        virtual std::unique_ptr<save_player_house> upgrade() = 0;
        virtual std::unique_ptr<save_player_house> downgrade() = 0;
    };

    class save_player_house_1 : public save_player_house {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_player_house_1() = default;
        save_player_house_1(const save_player_house_1&) = default;
        save_player_house_1(save_player_house_1&&) = default;
        save_player_house_1(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_player_house> upgrade() override;
        std::unique_ptr<save_player_house> downgrade() override;
    private:
        static const int m_size = 0x26400;
        u8 m_buffer[m_size];
    };

    class save_player_house_2 : public save_player_house {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_player_house_2() = default;
        save_player_house_2(const save_player_house_2&) = default;
        save_player_house_2(save_player_house_2&&) = default;
        save_player_house_2(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_player_house> upgrade() override;
        std::unique_ptr<save_player_house> downgrade() override;
    private:
        static const int m_size = 0x28A28;
        u8 m_buffer[m_size];
    };

    std::unique_ptr<save_player_house> get_save_player_house(u8 *data, u16 revision_in, u16 revision_out);

    std::vector<std::unique_ptr<save_player_house>> get_save_player_house_list(u8 *data, u16 revision_in, u16 revision_out);
};
