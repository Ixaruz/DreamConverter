#include <save_player_house_list.hpp>

namespace save_player_house
{
    std::vector<u16> revisions =
    {
        21, //1.11.0 (revision before upgrade)
        22 //2.0.0
    };

    static std::map<u16, std::function<std::unique_ptr<save_player_house>(u8*)>> constructors =
    {
        {21, [](u8* data){ return std::make_unique<save_player_house_1>(data); }},
        {22, [](u8* data){ return std::make_unique<save_player_house_2>(data); }}
    };

    u8 const *save_player_room_1::to_bin() { return m_buffer; }
    u8 const *save_player_room_2::to_bin() { return m_buffer; }
    u8 const *save_player_house_1::to_bin() { return m_buffer; }
    u8 const *save_player_house_2::to_bin() { return m_buffer; }

    int save_player_room_1::get_size() { return m_size; }
    int save_player_room_2::get_size() { return m_size; }
    int save_player_house_1::get_size() { return m_size; }
    int save_player_house_2::get_size() { return m_size; }

    void save_player_room_1::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_player_room_2::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_player_house_1::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_player_house_2::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }

    save_player_room_1::save_player_room_1 (u8 *data) { this->from_data(data); }
    save_player_room_2::save_player_room_2 (u8 *data) { this->from_data(data); }
    save_player_house_1::save_player_house_1 (u8 *data) { this->from_data(data); }
    save_player_house_2::save_player_house_2 (u8 *data) { this->from_data(data); }

    std::unique_ptr<save_player_room> save_player_room_1::downgrade()
    {
        return std::make_unique<save_player_room_1>(*(this));
    }

    std::unique_ptr<save_player_room> save_player_room_2::downgrade()
    {
        save_player_room_1 *res = new save_player_room_1();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_buffer, res->get_size());
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_player_room_1>(*(res));
    }

    std::unique_ptr<save_player_room> save_player_room_1::upgrade() {
        save_player_room_2 *res = new save_player_room_2();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_buffer, res->get_size());
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_player_room_2>(*(res));
    }

    std::unique_ptr<save_player_room> save_player_room_2::upgrade()
    {
        return std::make_unique<save_player_room_2>(*(this));
    }

    std::unique_ptr<save_player_house> save_player_house_1::downgrade()
    {
        return std::make_unique<save_player_house_1>(*(this));
    }

    std::unique_ptr<save_player_house> save_player_house_2::downgrade() {
        save_player_house_1 *res = new save_player_house_1();
        save_player_room_1 *room1 = new save_player_room_1();
        save_player_room_2 *room2 = new save_player_room_2();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_buffer, 0x120); // HouseLevel -> EventFlag
        for(int i = 0; i < 6; i++){
            memcpy(buffer + 0x120 + i * room1->get_size(),
                   save_player_room_2(m_buffer + 0x120 + i * room2->get_size()).downgrade()->to_bin(),
                   room1->get_size()); //RoomList
        }
        memcpy(buffer + 0x120 + (6 * room1->get_size()),
               m_buffer + 0x120 + (6 * room2->get_size()),
               0x30); // PlayerList -> Cockroach
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_player_house_1>(*(res));
    }

    std::unique_ptr<save_player_house> save_player_house_1::upgrade() {
        save_player_house_2 *res = new save_player_house_2();
        save_player_room_1 *room1 = new save_player_room_1();
        save_player_room_2 *room2 = new save_player_room_2();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_buffer, 0x120);
        for(int i = 0; i < 6; i++){
            memcpy(buffer + 0x120 + i * room2->get_size(),
                   save_player_room_1(m_buffer + 0x120 + i * room1->get_size()).upgrade()->to_bin(),
                   room1->get_size());
        }
        memcpy(buffer + 0x120 + (6 * room2->get_size()),
               m_buffer + 0x120 + (6 * room1->get_size()),
               0x30); // PlayerList -> Cockroach
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_player_house_2>(*(res));
    }

    std::unique_ptr<save_player_house> save_player_house_2::upgrade()
    {
        return std::make_unique<save_player_house_2>(*(this));
    }

    std::unique_ptr<save_player_house> get_save_player_house(u8 *data, u16 revision_in, u16 revision_out)
    {
        return save_struct::get_save_struct<save_player_house>(constructors,
                                                            revisions,
                                                            data,
                                                            revision_in,
                                                            revision_out);
    }

    std::vector<std::unique_ptr<save_player_house>> get_save_player_house_list(u8 *data, u16 revision_in, u16 revision_out) {
        std::vector<std::unique_ptr<save_player_house>> res;
        int house_size = save_struct::create_save_struct(constructors, save_struct::get_clamped_revision(revisions, revision_in), data)->get_size();
        for(int house_index = 0; house_index < 8; house_index++){
            res.push_back(std::move(get_save_player_house(data + (house_index * house_size), revision_in, revision_out)));
        }
        return res;
    }
}
