#include "save_structs/save_npc_house_list.hpp"

namespace
{ //anonymous
    static u8 footer[] =
    {
        0x4B, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4B, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x9B, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x40,
        0x10, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    static int footer_size = sizeof(footer);
}

namespace save_npc_house
{
    std::vector<u16> revisions =
    {
        21, //1.11.0 (revision before upgrade)
        22 //2.0.0
    };

    static std::map<u16, std::function<std::unique_ptr<save_npc_house>(u8*)>> constructors =
    {
        {21, [](u8* data){ return std::make_unique<save_npc_house_1>(data); }},
        {22, [](u8* data){ return std::make_unique<save_npc_house_2>(data); }}
    };

    u8 const *save_npc_house_1::to_bin() { return m_buffer; }
    u8 const *save_npc_house_2::to_bin() { return m_buffer; }

    int save_npc_house_1::get_size() { return m_size; }
    int save_npc_house_2::get_size() { return m_size; }

    void save_npc_house_1::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_npc_house_2::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }

    save_npc_house_1::save_npc_house_1 (u8 *data) { this->from_data(data); }
    save_npc_house_2::save_npc_house_2 (u8 *data) { this->from_data(data); }

    std::unique_ptr<save_npc_house> save_npc_house_1::downgrade()
    {
        return std::make_unique<save_npc_house_1>(*(this));
    }

    std::unique_ptr<save_npc_house> save_npc_house_2::downgrade()
    {
        save_npc_house_1 *res = new save_npc_house_1();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_buffer, res->get_size());
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_npc_house_1>(*(res));
    }

    std::unique_ptr<save_npc_house> save_npc_house_1::upgrade() {
        save_npc_house_2 *res = new save_npc_house_2();
        u8 *buffer = new u8[res->get_size()]{0};
        u16 empty_item = 0xFFFE;
        memcpy(buffer, m_buffer, this->get_size());
        for (int i = 0; i < 236; i++)
            //0xC is the size of an item in the ::Game::SaveWherearenItemPlacementData struct
            memcpy(buffer + 0x1D8 + (i * 0xC), &empty_item, sizeof(empty_item));
        memcpy(buffer + 0x1270, footer, footer_size);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_npc_house_2>(*(res));
    }

    std::unique_ptr<save_npc_house> save_npc_house_2::upgrade()
    {
        return std::make_unique<save_npc_house_2>(*(this));
    }


    std::unique_ptr<save_npc_house> get_save_npc_house(u8 *data, u16 revision_in, u16 revision_out)
    {
        return save_struct::get_save_struct<save_npc_house>(constructors,
                                                            revisions,
                                                            data,
                                                            revision_in,
                                                            revision_out);
    }

    std::vector<std::unique_ptr<save_npc_house>> get_save_npc_house_list(u8 *data, u16 revision_in, u16 revision_out) {
        std::vector<std::unique_ptr<save_npc_house>> res;
        int house_size = save_struct::create_save_struct(constructors, save_struct::get_clamped_revision(revisions, revision_in), data)->get_size();
        for(int house_index = 0; house_index < 10; house_index++){
            res.push_back(std::move(get_save_npc_house(data + (house_index * house_size), revision_in, revision_out)));
        }
        return res;
    }
};
