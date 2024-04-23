#include <save_player_house_list.hpp>

namespace save_player_house {

    u8 *player_room_1::get_everything() {return everything;}

    player_room_1::player_room_1(void *data) {
        memcpy(everything, data, size);
    }

    u8 *player_room_2::get_everything() {return everything;}

    player_room_2::player_room_2(void *data) {
        memcpy(everything, data, size);
    }

    player_room_1 player_room_2::downgrade()
    {
        u8 *buffer = new u8[player_room_1::get_size()]{0};
        memcpy(buffer, everything, player_room_1::get_size());
        player_room_1 res = player_room_1(buffer);
        delete buffer;
        return res;
    }

    player_room_2 upgrade(player_room_1 player_room) {
        u8 *buffer = new u8[0x6C24]{0};
        memcpy(buffer, player_room.get_everything(), player_room_1::get_size());
        player_room_2 res = player_room_2(buffer);
        delete buffer;
        return res;
    }

    u8 *save_player_house_1::get_everything() {
        u8 *buffer = new u8[size];
        memcpy(buffer, everything, size);
        return buffer;
    }

    save_player_house_1::save_player_house_1(void *data) {
        memcpy(everything, data, size);
    }

    u8 *save_player_house_2::get_everything() {
        u8 *buffer = new u8[size];
        memcpy(buffer, everything, size);
        return buffer;
    }

    save_player_house_2::save_player_house_2(void *data) {
        memcpy(everything, data, size);
    }

    save_player_house_1 *save_player_house_2::downgrade() {
        u8 *buffer = new u8[save_player_house_1::get_size()]{0};
        memcpy(buffer, everything, 0x120);
        for(int i = 0; i < 6; i++){
            memcpy(buffer + 0x120 + i * player_room_1::get_size(),
            player_room_2(everything + 0x120 + i * player_room_2::get_size()).downgrade().get_everything(),
            player_room_1::get_size());
        }
        memcpy(buffer + 0x263D0, everything + 0x289F8, 0x30);
        return new save_player_house_1(buffer);
    }

    save_player_house_2 *upgrade(save_player_house_1 save_player_house) {
        u8 *buffer = new u8[save_player_house_2::get_size()]{0};
        u8 *everything = save_player_house.get_everything();
        memcpy(buffer, everything, 0x120);
        for(int i = 0; i < 6; i++){
            memcpy(buffer + 0x120 + i * player_room_2::get_size(),
            upgrade(player_room_1(everything + 0x120 + i * player_room_1::get_size())).get_everything(),
            player_room_1::get_size());
        }
        memcpy(buffer + 0x289F8, everything + 0x263D0, 0x30);
        return new save_player_house_2(buffer);
    }

    std::unique_ptr<save_player_house_1 *> get_save_player_house(void *data, u16 revision_in, u16 revision_out, save_player_house_type &type) {    
        switch(revision_out) {
            case 0 ... 21:
            {
                type = save_player_house_type::type_1;
                switch(revision_in) {
                    case 0 ... 21:
                        return std::make_unique<save_player_house_1 *>(new save_player_house_1(data));
                    case 22 ... 28:
                        return std::make_unique<save_player_house_1 *>(save_player_house_2(data).downgrade());
                    default: 
                        break;
                }
            }
                break;
            case 22 ... 28:
            {
                type = save_player_house_type::type_2;
                switch(revision_in) {
                    case 0 ... 21:
                        return std::make_unique<save_player_house_1 *>(upgrade(save_player_house_1(data)));
                    case 22 ... 28:
                        return std::make_unique<save_player_house_1 *>(new save_player_house_2(data));
                    default: 
                        break;
                }
            }
                break;
            default:
                type = save_player_house_type::none;
                return std::make_unique<save_player_house_1 *>(nullptr);
                break;
        }
    }

    std::vector<std::unique_ptr<save_player_house_1 *>> get_save_player_house_list(void *data, u16 revision_in, u16 revision_out, save_player_house_type &type) {    
        std::vector<std::unique_ptr<save_player_house_1 *>> res;
        type = save_player_house_type::none;
        for(int house_index = 0; house_index < 8; house_index++){
            switch(revision_out) {
            case 0 ... 21:
            {
                type = save_player_house_type::type_1;
                switch(revision_in) {
                    case 0 ... 21: {
                        res.push_back(std::move(std::make_unique<save_player_house_1 *>(new save_player_house_1((u8 *)data + (house_index * save_player_house_1::get_size())))));
                    }
                    case 22 ... 28: {
                        res.push_back(std::move(std::make_unique<save_player_house_1 *>(save_player_house_2((u8 *)data + (house_index * save_player_house_2::get_size())).downgrade())));
                    }
                    default: 
                        break;
                }
            }
                break;
            case 22 ... 28:
            {
                type = save_player_house_type::type_2;
                switch(revision_in) {
                    case 0 ... 21: {
                        res.push_back(std::move(std::make_unique<save_player_house_1 *>(upgrade(save_player_house_1((u8 *)data + (house_index * save_player_house_1::get_size()))))));
                    }
                    case 22 ... 28: {
                        res.push_back(std::move(std::make_unique<save_player_house_1 *>(new save_player_house_2((u8 *)data + (house_index * save_player_house_2::get_size())))));
                    }
                    default: 
                        break;
                }
            }
                break;
            default:
                type = save_player_house_type::none;
                res.push_back(std::move(std::make_unique<save_player_house_1 *>(nullptr)));
                break;
            }
        }
        return res;
    }
}
