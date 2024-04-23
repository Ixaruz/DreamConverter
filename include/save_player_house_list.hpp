#pragma once
#include <types.hpp>
#include <cstring>
#include <memory>
#include <vector>

namespace save_player_house {

    class player_room_1 {
    protected:
        static const int size = 0x65C8;
        u8 everything[0x65C8];
        player_room_1() = default;
    public:
        static const int get_size() {return size;}

        virtual u8 *get_everything();

        player_room_1(void *data);
    };

    class player_room_2 : public player_room_1 {
    protected:
        static const int size = 0x6C24;
        u8 everything[0x6C24];
    public:
        static const int get_size() {return size;}

        u8 *get_everything() override;

        player_room_2(void *data);

        player_room_1 downgrade();
    };

    player_room_2 upgrade(player_room_1 player_room);

    enum class save_player_house_type{
        none = 0,
        type_1,
        type_2
    };

    class save_player_house_1 {
    protected:
        static const int size = 0x26400;
        u8 everything[size];

        save_player_house_1() = default;
    public:
        static const int get_size() {return size;}

        virtual u8 *get_everything();
        
        save_player_house_1(void *data);
    };

    class save_player_house_2: public save_player_house_1 {
    protected:
        static const int size = 0x28A28;
        u8 everything[size];
    public:
        static const int get_size() {return size;}

        u8 *get_everything() override;

        save_player_house_2(void *data);
        
        save_player_house_1 *downgrade();
    };

    save_player_house_2 *upgrade(save_player_house_1 save_player_house);

    std::unique_ptr<save_player_house_1 *> get_save_player_house(void *data, u16 revision_in, u16 revision_out, save_player_house_type &type);
    
    std::vector<std::unique_ptr<save_player_house_1 *>> get_save_player_house_list(void *data, u16 revision_in, u16 revision_out, save_player_house_type &type);
}
