#include <save_npc_house_list.hpp>

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
    u8 const *save_npc_house_1::to_bin() { return m_buffer; }
    u8 const *save_npc_house_2::to_bin() { return m_buffer; }

    int const save_npc_house_1::get_size() { return m_size; }
    int const save_npc_house_2::get_size() { return m_size; }

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
            memcpy(buffer + 0x1D8 + (i * 0xC), &empty_item, sizeof(u16));
        memcpy(buffer + 0x1270, footer, footer_size);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_npc_house_2>(*(res));
    }

    std::unique_ptr<save_npc_house> save_npc_house_2::upgrade()
    {
        return std::make_unique<save_npc_house_2>(*(this));
    }


    std::unique_ptr<save_npc_house> get_save_npc_house(u8 *data, u16 revision_in, u16 revision_out, save_npc_house_type &type) {    
        switch(revision_out) {
            case 0 ... 21:
            {
                type = save_npc_house_type::type_1;
                switch(revision_in) {
                    case 0 ... 21:
                        return std::make_unique<save_npc_house_1>(data);
                    case 22 ... 28:
                        return save_npc_house_2(data).downgrade();
                    default: 
                        break;
                }
            }
            case 22 ... 28:
            {
                type = save_npc_house_type::type_2;
                switch(revision_in) {
                    case 0 ... 21:
                        return save_npc_house_1(data).upgrade();
                    case 22 ... 28:
                        return std::make_unique<save_npc_house_2>(data);
                    default: 
                        break;
                }
            }
            default:
                type = save_npc_house_type::none;
                return std::make_unique<save_npc_house>(nullptr);
                break;
        }
    }

    std::vector<std::unique_ptr<save_npc_house>> get_save_npc_house_list(u8 *data, u16 revision_in, u16 revision_out, save_npc_house_type &type) {    
        std::vector<std::unique_ptr<save_npc_house>> res;
        save_npc_house_1 *npc_house_1 = new save_npc_house_1();
        save_npc_house_2 *npc_house_2 = new save_npc_house_2();
        for(int house_index = 0; house_index < 8; house_index++){
            switch(revision_out) {
            case 0 ... 21:
            {
                type = save_npc_house_type::type_1;
                switch(revision_in) {
                    case 0 ... 21: {
                        res.push_back(std::move(std::make_unique<save_npc_house_1>(new save_npc_house_1((u8 *)data + (house_index * npc_house_1->get_size())))));
                    }
                    case 22 ... 28: {
                        res.push_back(std::move(save_npc_house_2((u8 *)data + (house_index * npc_house_2->get_size())).downgrade()));
                    }
                    default: 
                        break;
                }
            }
            case 22 ... 28:
            {
                type = save_npc_house_type::type_2;
                switch(revision_in) {
                    case 0 ... 21: {
                        res.push_back(std::move(save_npc_house_1((u8 *)data + (house_index * npc_house_1->get_size())).upgrade()));
                    }
                    case 22 ... 28: {
                        res.push_back(std::move(std::make_unique<save_npc_house_2>(new save_npc_house_1((u8 *)data + (house_index * npc_house_1->get_size())))));
                    }
                    default: 
                        break;
                }
            }
            default:
                type = save_npc_house_type::none;
                res.push_back(std::move(std::make_unique<save_npc_house_1>(nullptr)));
            }
        }
        delete npc_house_1;
        delete npc_house_1;
        return res;
    }
};
