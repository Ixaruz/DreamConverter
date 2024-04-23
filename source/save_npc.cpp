#include <save_npc.hpp>

namespace save_npc {
    u8 const *save_npc_1::to_bin() { return m_buffer; }
    u8 const *save_npc_2::to_bin() { return m_buffer; }
    u8 const *save_npc_3::to_bin() { return m_buffer; }

    int const save_npc_1::get_size() { return m_size; }
    int const save_npc_2::get_size() { return m_size; }
    int const save_npc_3::get_size() { return m_size; }

    void save_npc_1::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_npc_2::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_npc_3::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }

    save_npc_1::save_npc_1 (u8 *data) { this->from_data(data); }
    save_npc_2::save_npc_2 (u8 *data) { this->from_data(data); }
    save_npc_3::save_npc_3 (u8 *data) { this->from_data(data); }

    std::unique_ptr<save_npc> save_npc_1::downgrade()
    {
        return std::make_unique<save_npc_1>(*(this));
    }

    std::unique_ptr<save_npc> save_npc_2::downgrade()
    {
        save_npc_1 *res = new save_npc_1();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset_res = 0;
        u32 offset_in =  0;
        for(int animal = 0; animal < 10; animal++) {
            //copy everything until LightMemory
            memcpy(buffer + offset_res, m_buffer + offset_in, 0x2F84);
            offset_res  += 0x2F84;
            offset_in   += 0x2F84;
            //fix LightMemory
            for(int i = 0; i < 160; i++){
                memcpy(buffer + offset_res, m_buffer + offset_in, 0x14C);
                offset_res +=   0x14C;
                offset_in +=    0x158;
            }
            //copy everything after LightMemory
            memcpy(buffer + offset_res, m_buffer + offset_in, 0x13230 - (0x2F84 + 0x158 * 160));
            offset_res +=   0x13230 - (0x2F84 + 0x158 * 160);
            offset_in +=    0x13230 - (0x2F84 + 0x158 * 160);
        }
        //GrowBitArray
        memcpy(buffer + offset_res, m_buffer + offset_in, 4 * 36);
        offset_res +=   4 * 36;
        offset_in +=    4 * 36;
        
        //MoveInAnimal & MoveOutAnimal
        for(int animal = 0; animal < 14; animal++) {
            //copy everything until LightMemory
            memcpy(buffer + offset_res, m_buffer + offset_in, 0x2F84);
            offset_res  += 0x2F84;
            offset_in   += 0x2F84;
            //fix LightMemory
            for(int i = 0; i < 160; i++){
                memcpy(buffer + offset_res, m_buffer + offset_in, 0x14C);
                offset_res +=   0x14C;
                offset_in +=    0x158;
            }
            memcpy(buffer + offset_res, m_buffer + offset_in, 0x13230 - (0x2F84 + 0x158 * 160));
            offset_res +=   0x13230 - (0x2F84 + 0x158 * 160);
            offset_in +=    0x13230 - (0x2F84 + 0x158 * 160);
        }
        //copy after LightMemory
        memcpy(buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_in);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_npc_1>(*(res));
    }

    std::unique_ptr<save_npc> save_npc_3::downgrade()
    {
        save_npc_2 *res = new save_npc_2();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset = 0x1CB6BC + 400 * 232;
        //copy everything until NpcBirthdayHouse (after NpcArchive)
        memcpy(buffer, m_buffer, offset);
        //skip 20 archived Npcs
        int save_npc_2_size = 0x1D6D48;
        memcpy(buffer + offset, m_buffer + offset + 20 * 232, res->get_size() - offset);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_npc_2>(*(res));
    }

    std::unique_ptr<save_npc> save_npc_1::upgrade()
    {
        save_npc_2 *res = new save_npc_2();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset_res = 0;
        u32 offset_in =  0;
        for(int animal = 0; animal < 10; animal++) {
            //copy everything until LightMemory
            memcpy(buffer + offset_res, m_buffer + offset_in, 0x2F84);
            offset_res  += 0x2F84;
            offset_in   += 0x2F84;
            //fix LightMemory
            for(int i = 0; i < 160; i++){
                memcpy(buffer + offset_res, m_buffer + offset_in, 0x14C);
                offset_res +=   0x158;
                offset_in +=    0x14C;
            }
            memcpy(buffer + offset_res, m_buffer + offset_in, 0x13230 - (0x2F84 + 0x158 * 160));
            offset_res +=   0x13230 - (0x2F84 + 0x158 * 160);
            offset_in +=    0x13230 - (0x2F84 + 0x158 * 160);
        }
        //GrowBitArray
        memcpy(buffer + offset_res, m_buffer + offset_in, 4 * 36);
        offset_res +=   4 * 36;
        offset_in +=    4 * 36;
        
        //MoveInAnimal & MoveOutAnimal
        for(int animal = 0; animal < 14; animal++) {
            //copy everything until LightMemory
            memcpy(buffer + offset_res, m_buffer + offset_in, 0x2F84);
            offset_res  += 0x2F84;
            offset_in   += 0x2F84;
            //fix LightMemory
            for(int i = 0; i < 160; i++){
                memcpy(buffer + offset_res, m_buffer + offset_in, 0x14C);
                offset_res +=   0x158;
                offset_in +=    0x14C;
            }
            memcpy(buffer + offset_res, m_buffer + offset_in, 0x13230 - (0x2F84 + 0x158 * 160));
            offset_res +=   0x13230 - (0x2F84 + 0x158 * 160);
            offset_in +=    0x13230 - (0x2F84 + 0x158 * 160);
        }
        //copy after LightMemory
        memcpy(buffer + offset_res, m_buffer + offset_in, this->get_size() - offset_in);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_npc_2>(*(res));
    }

    std::unique_ptr<save_npc> save_npc_2::upgrade()
    {
        save_npc_3 *res = new save_npc_3();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset = 0x1CB6BC + 400 * 232;
        //copy everything until NpcBirthdayHouse (after NpcArchive)
        memcpy(buffer, m_buffer, offset);
        //leave 20 archived Npcs empty
        memcpy(buffer + offset + 20 * 232, m_buffer + offset, this->get_size() - offset);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_npc_3>(*(res));
    }

    std::unique_ptr<save_npc> save_npc_3::upgrade()
    {
        return std::make_unique<save_npc_3>(*(this));
    }


    std::unique_ptr<save_npc> get_save_npc(u8 *data, u16 revision_in, u16 revision_out, save_npc_type &type) {    
        switch(revision_out) {
            case 0 ... 12:
            {
                type = save_npc_type::type_1;
                switch(revision_in) {
                    case 0 ... 12:
                        return std::make_unique<save_npc_1>(data);
                    case 13 ... 21:
                        return save_npc_2(data).downgrade();
                    case 22 ... 28:
                        // this is likely going to break as the second downgrade is being called from the save_npc function and not the save_npc_2 function. i dont know how to properly cast it to do that.
                        return save_npc_3(data).downgrade()->downgrade();
                    default: 
                        break;
                }
            }
                break;
            case 13 ... 21:
            {
                type = save_npc_type::type_2;
                switch(revision_in) {
                    case 0 ... 12:
                        return save_npc_1(data).upgrade();
                    case 13 ... 21:
                        return std::make_unique<save_npc_2>(data);
                    case 22 ... 28:
                        return save_npc_3(data).downgrade();
                    default: 
                        break;
                }
            }
                break;
            case 22 ... 28:
            {
                type = save_npc_type::type_3;
                switch(revision_in) {
                    case 0 ... 12:
                        return save_npc_1(data).upgrade()->upgrade();
                    case 13 ... 21:
                        return save_npc_2(data).upgrade();
                    case 22 ... 28:
                        return std::make_unique<save_npc_3>(data);
                    default: 
                        break;
                }
            }
                break;
            default:
                type = save_npc_type::none;
                return std::make_unique<save_npc_1>(nullptr);
                break;
        }
    }
}
