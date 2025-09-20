#include "save_structs/save_shop.hpp"

namespace save_shop
{

    std::vector<u16> revisions =
    {
        12, //1.4.2 (revision before upgrade)
        13, //1.5.0
        15, //1.6.0
        16, //1.7.0
        18, //1.9.0
        22  //2.0.0
    };

    static std::map<u16, std::function<std::unique_ptr<save_shop>(u8*)>> constructors =
    {
        {12, [](u8* data){ return std::make_unique<save_shop_1>(data); }},
        {13, [](u8* data){ return std::make_unique<save_shop_2>(data); }},
        {15, [](u8* data){ return std::make_unique<save_shop_3>(data); }},
        {16, [](u8* data){ return std::make_unique<save_shop_4>(data); }},
        {18, [](u8* data){ return std::make_unique<save_shop_5>(data); }},
        {22, [](u8* data){ return std::make_unique<save_shop_6>(data); }}
    };

    u8 const *save_shop_1::to_bin() { return m_buffer; }
    u8 const *save_shop_2::to_bin() { return m_buffer; }
    u8 const *save_shop_3::to_bin() { return m_buffer; }
    u8 const *save_shop_4::to_bin() { return m_buffer; }
    u8 const *save_shop_5::to_bin() { return m_buffer; }
    u8 const *save_shop_6::to_bin() { return m_buffer; }

    int save_shop_1::get_size() { return m_size; }
    int save_shop_2::get_size() { return m_size; }
    int save_shop_3::get_size() { return m_size; }
    int save_shop_4::get_size() { return m_size; }
    int save_shop_5::get_size() { return m_size; }
    int save_shop_6::get_size() { return m_size; }

    void save_shop_1::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_shop_2::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_shop_3::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_shop_4::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_shop_5::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_shop_6::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }

    save_shop_1::save_shop_1 (u8 *data) { this->from_data(data); }
    save_shop_2::save_shop_2 (u8 *data) { this->from_data(data); }
    save_shop_3::save_shop_3 (u8 *data) { this->from_data(data); }
    save_shop_4::save_shop_4 (u8 *data) { this->from_data(data); }
    save_shop_5::save_shop_5 (u8 *data) { this->from_data(data); }
    save_shop_6::save_shop_6 (u8 *data) { this->from_data(data); }

    std::unique_ptr<save_shop> save_shop_1::downgrade()
    {
        return std::make_unique<save_shop_1>(*(this));
    }

    std::unique_ptr<save_shop> save_shop_2::downgrade() {
        save_shop_1 *res = new save_shop_1();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, m_buffer, 0x2C);
        //ShopTailor
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x12D4);
        offset_res += 0x12D4;
        offset_in += 0x12D4 + 0x18;
        //ShopShoes
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x100);
        offset_res += 0x100;
        offset_in += 0x100 + 0x10;
        //ShopZakka
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x16D0);
        offset_res += 0x16D0;
        offset_in += 0x16D0 + 0x18;
        //remainder
        memcpy(buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_res);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_shop_1>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_3::downgrade() {
        save_shop_2 *res = new save_shop_2();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, m_buffer, 0x2C);
        //ShopTailor
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x12EC);
        offset_res += 0x12EC;
        offset_in += 0x12EC + 0x50;
        //ShopShoes
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x16E8);
        offset_res += 0x16E8;
        offset_in += 0x16E8 + 0x80;
        //remainder
        memcpy(buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_res);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_shop_2>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_4::downgrade() {
        save_shop_3 *res = new save_shop_3();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, m_buffer, 0x2C);
        //ShopTailor
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x133C);
        offset_res += 0x133C;
        offset_in += 0x133C + 0x50;
        //ShopShoes
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x1768);
        offset_res += 0x1768;
        offset_in += 0x1768 + 0x80;
        //ShopKabu
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x44);
        offset_res += 0x44;
        offset_in += 0x44;
        //ShopCatalog
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x200);
        offset_res += 0x200;
        offset_in += 0x200 + 0x100;
        //remainder
        memcpy(buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_res);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_shop_3>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_5::downgrade() {
        save_shop_4 *res = new save_shop_4();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, m_buffer, 0x2C);
        //ShopTailor
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x138C);
        offset_res += 0x138C;
        offset_in += 0x138C + 0x50;
        //ShopShoes
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy(buffer + offset_res, m_buffer + offset_in, 0x17E8);
        offset_res += 0x17E8;
        offset_in += 0x17E8 + 0x40;
        //remainder
        memcpy(buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_res);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_shop_4>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_6::downgrade() {
        save_shop_5 *res = new save_shop_5();
        u8 *buffer = new u8[res->get_size()]{0};
        //everything before ShopCommune
        memcpy(buffer, m_buffer, res->get_size());
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_shop_5>(*(res));
    }

    ////UPGRADE/////

    std::unique_ptr<save_shop> save_shop_1::upgrade() {
        save_shop_2 *res = new save_shop_2();
        //64 bit for empty items
        u64 *buffer = new u64[res->get_size()]{0xFFFE};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, m_buffer, 0x2C);
        //ShopTailor
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x12D4);
        offset_res += 0x12D4 + 0x18;
        offset_in += 0x12D4;
        //ShopShoes
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x100);
        offset_res += 0x100 + 0x10;
        offset_in += 0x100;
        //ShopZakka
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x16D0);
        offset_res += 0x16D0 + 0x18;
        offset_in += 0x16D0;
        //remainder
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_res);
        res->from_data((u8 *)buffer);
        delete buffer;
        return std::make_unique<save_shop_2>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_2::upgrade() {
        save_shop_3 *res = new save_shop_3();
        //64 bit for empty items
        u64 *buffer = new u64[res->get_size()]{0xFFFE};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy((u8 *)buffer, m_buffer, 0x2C);
        //ShopTailor
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x12EC);
        offset_res += 0x12EC + 0x50;
        offset_in += 0x12EC;
        //ShopShoes
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x16E8);
        offset_res += 0x16E8 + 0x80;
        offset_in += 0x16E8;
        //remainder
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_res);
        res->from_data((u8 *)buffer);
        delete buffer;
        return std::make_unique<save_shop_3>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_3::upgrade() {
        save_shop_4 *res = new save_shop_4();
        //64 bit for empty items
        u64 *buffer = new u64[res->get_size()]{0xFFFE};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy((u8 *)buffer, m_buffer, 0x2C);
        //ShopTailor
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x133C);
        offset_res += 0x133C + 0x50;
        offset_in += 0x133C;
        //ShopShoes
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x1768);
        offset_res += 0x1768 + 0x80;
        offset_in += 0x1768;
        //ShopKabu
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x44);
        offset_res += 0x44;
        offset_in += 0x44;
        //ShopCatalog
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x200);
        offset_res += 0x200 + 0x100;
        offset_in += 0x200;
        //remainder
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_res);
        res->from_data((u8 *)buffer);
        delete buffer;
        return std::make_unique<save_shop_4>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_4::upgrade() {
        save_shop_5 *res = new save_shop_5();
        //64 bit for empty items
        u64 *buffer = new u64[res->get_size()]{0xFFFE};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy((u8 *)buffer, m_buffer, 0x2C);
        //ShopTailor
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x138C);
        offset_res += 0x138C + 0x50;
        offset_in += 0x138C;
        //ShopShoes
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, 0x17E8);
        offset_res += 0x17E8 + 0x40;
        offset_in += 0x17E8;
        //remainder
        memcpy((u8 *)buffer + offset_res, m_buffer + offset_in, res->get_size() - offset_res);
        res->from_data((u8 *)buffer);
        delete buffer;
        return std::make_unique<save_shop_5>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_5::upgrade() {
        save_shop_6 *res = new save_shop_6();
        u8 *buffer = new u8[res->get_size()]{0};
        //everything before ShopCommune
        memcpy((u8 *)buffer, m_buffer, res->get_size());
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_shop_6>(*(res));
    }

    std::unique_ptr<save_shop> save_shop_6::upgrade()
    {
        return std::make_unique<save_shop_6>(*(this));
    }

    std::unique_ptr<save_shop> get_save_shop(u8 *data, u16 revision_in, u16 revision_out)
    {
        return save_struct::get_save_struct<save_shop>(constructors,
                                                       revisions,
                                                       data,
                                                       revision_in,
                                                       revision_out);
    }
}
