#include <save_shop.hpp>

namespace save_shop {
    u8 *save_shop_1::get_everything() {
        return everything;
    }
    u8 *save_shop_2::get_everything() {
        return everything;
    }
    u8 *save_shop_3::get_everything() {
        return everything;
    }
    u8 *save_shop_4::get_everything() {
        return everything;
    }
    u8 *save_shop_5::get_everything() {
        return everything;
    }
    u8 *save_shop_6::get_everything() {
        return everything;
    }

    save_shop_1::save_shop_1(void *data) {
        memcpy(everything, data, size);
    }

    save_shop_2::save_shop_2(void *data) {
        memcpy(everything, data, size);
    }

    save_shop_3::save_shop_3(void *data) {
        memcpy(everything, data, size);
    }

    save_shop_4::save_shop_4(void *data) {
        memcpy(everything, data, size);
    }

    save_shop_5::save_shop_5(void *data) {
        memcpy(everything, data, size);
    }

    save_shop_6::save_shop_6(void *data) {
        memcpy(everything, data, size);
    }

    save_shop_1 *save_shop_2::downgrade() {
        u8 *buffer = new u8[save_shop_1::get_size()]{0};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, everything, 0x2C);
        //ShopTailor
        memcpy(buffer + offset_res, everything + offset_in, 0x12D4);
        offset_res += 0x12D4;
        offset_in += 0x12D4 + 0x18;
        //ShopShoes
        memcpy(buffer + offset_res, everything + offset_in, 0x100);
        offset_res += 0x100;
        offset_in += 0x100 + 0x10;
        //ShopZakka
        memcpy(buffer + offset_res, everything + offset_in, 0x16D0);
        offset_res += 0x16D0;
        offset_in += 0x16D0 + 0x18;
        //rest
        memcpy(buffer + offset_res, everything + offset_in, save_shop_1::get_size() - offset_res);
        save_shop_1 *res = new save_shop_1(buffer);
        delete buffer;
        return res;
    }

    save_shop_2 *save_shop_3::downgrade() {
        u8 *buffer = new u8[save_shop_2::get_size()]{0};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, everything, 0x2C);
        //ShopTailor
        memcpy(buffer + offset_res, everything + offset_in, 0x12EC);
        offset_res += 0x12EC;
        offset_in += 0x12EC + 0x50;
        //ShopShoes
        memcpy(buffer + offset_res, everything + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy(buffer + offset_res, everything + offset_in, 0x16E8);
        offset_res += 0x16E8;
        offset_in += 0x16E8 + 0x80;
        //rest
        memcpy(buffer + offset_res, everything + offset_in, save_shop_2::get_size() - offset_res);
        save_shop_2 *res = new save_shop_2(buffer);
        delete buffer;
        return res;
    }

    save_shop_3 *save_shop_4::downgrade() {
        u8 *buffer = new u8[save_shop_3::get_size()]{0};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, everything, 0x2C);
        //ShopTailor
        memcpy(buffer + offset_res, everything + offset_in, 0x133C);
        offset_res += 0x133C;
        offset_in += 0x133C + 0x50;
        //ShopShoes
        memcpy(buffer + offset_res, everything + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy(buffer + offset_res, everything + offset_in, 0x1768);
        offset_res += 0x1768;
        offset_in += 0x1768 + 0x80;
        //ShopKabu
        memcpy(buffer + offset_res, everything + offset_in, 0x44);
        offset_res += 0x44;
        offset_in += 0x44;
        //ShopCatalog
        memcpy(buffer + offset_res, everything + offset_in, 0x200);
        offset_res += 0x200;
        offset_in += 0x200 + 0x100;
        //rest
        memcpy(buffer + offset_res, everything + offset_in, save_shop_3::get_size() - offset_res);
        save_shop_3 *res = new save_shop_3(buffer);
        delete buffer;
        return res;
    }

    save_shop_4 *save_shop_5::downgrade() {
        u8 *buffer = new u8[save_shop_4::get_size()]{0};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, everything, 0x2C);
        //ShopTailor
        memcpy(buffer + offset_res, everything + offset_in, 0x138C);
        offset_res += 0x138C;
        offset_in += 0x138C + 0x50;
        //ShopShoes
        memcpy(buffer + offset_res, everything + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy(buffer + offset_res, everything + offset_in, 0x17E8);
        offset_res += 0x17E8;
        offset_in += 0x17E8 + 0x40;
        //rest
        memcpy(buffer + offset_res, everything + offset_in, save_shop_4::get_size() - offset_res);
        save_shop_4 *res = new save_shop_4(buffer);
        delete buffer;
        return res;
    }

    save_shop_5 *save_shop_6::downgrade() {
        u8 *buffer = new u8[save_shop_5::get_size()]{0};
        //everything before ShopCommune
        memcpy(buffer, everything, save_shop_5::get_size());
        save_shop_5 *res = new save_shop_5(buffer);
        delete buffer;
        return res;
    }

    ////UPGRADE/////

    save_shop_2 *upgrade(save_shop_1 save_shop) {
        //64 bit for empty items
        u64 *buffer = new u64[save_shop_2::get_size()]{0xFFFE};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy(buffer, save_shop.get_everything(), 0x2C);
        //ShopTailor
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x12D4);
        offset_res += 0x12D4 + 0x18;
        offset_in += 0x12D4;
        //ShopShoes
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x100);
        offset_res += 0x100 + 0x10;
        offset_in += 0x100;
        //ShopZakka
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x16D0);
        offset_res += 0x16D0 + 0x18;
        offset_in += 0x16D0;
        //rest
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, save_shop_2::get_size() - offset_res);
        save_shop_2 *res = new save_shop_2(buffer);
        delete buffer;
        return res;
    }

    save_shop_3 *upgrade(save_shop_2 save_shop) {
        u64 *buffer = new u64[save_shop_3::get_size()]{0xFFFE};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy((u8 *)buffer, save_shop.get_everything(), 0x2C);
        //ShopTailor
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x12EC);
        offset_res += 0x12EC + 0x50;
        offset_in += 0x12EC;
        //ShopShoes
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x16E8);
        offset_res += 0x16E8 + 0x80;
        offset_in += 0x16E8; 
        //rest
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, save_shop_3::get_size() - offset_res);
        save_shop_3 *res = new save_shop_3(buffer);
        delete buffer;
        return res;
    }

    save_shop_4 *upgrade(save_shop_3 save_shop) {
        u64 *buffer = new u64[save_shop_4::get_size()]{0xFFFE};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy((u8 *)buffer, save_shop.get_everything(), 0x2C);
        //ShopTailor
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x133C);
        offset_res += 0x133C + 0x50;
        offset_in += 0x133C;
        //ShopShoes
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x1768);
        offset_res += 0x1768 + 0x80;
        offset_in += 0x1768;
        //ShopKabu
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x44);
        offset_res += 0x44;
        offset_in += 0x44;
        //ShopCatalog
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x200);
        offset_res += 0x200 + 0x100;
        offset_in += 0x200;
        //rest
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, save_shop_4::get_size() - offset_res);
        save_shop_4 *res = new save_shop_4(buffer);
        delete buffer;
        return res;
    }

    save_shop_5 *upgrade(save_shop_4 save_shop) {
        u64 *buffer = new u64[save_shop_5::get_size()]{0xFFFE};
        u32 offset_res = 0x2C;
        u32 offset_in =  0x2C;
        //everything before ShopTailor
        memcpy((u8 *)buffer, save_shop.get_everything(), 0x2C);
        //ShopTailor
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x138C);
        offset_res += 0x138C + 0x50;
        offset_in += 0x138C;
        //ShopShoes
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x110);
        offset_res += 0x110;
        offset_in += 0x110;
        //ShopZakka
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, 0x17E8);
        offset_res += 0x17E8 + 0x40;
        offset_in += 0x17E8;
        //rest
        memcpy((u8 *)buffer + offset_res, save_shop.get_everything() + offset_in, save_shop_5::get_size() - offset_res);
        save_shop_5 *res = new save_shop_5(buffer);
        delete buffer;
        return res;
    }

    save_shop_6 *upgrade(save_shop_5 save_shop) {
        u8 *buffer = new u8[save_shop_6::get_size()]{0};
        //everything before ShopCommune
        memcpy((u8 *)buffer, save_shop.get_everything(), save_shop_5::get_size());
        save_shop_6 *res = new save_shop_6(buffer);
        delete buffer;
        return res;
    }
}