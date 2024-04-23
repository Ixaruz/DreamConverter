#pragma once
#include <types.hpp>
#include <cstring>
#include <memory>

namespace save_shop {
    //can all be upgraded easily; just need to fill the gaps with empty items; except in ShopCommune, needs to be filled with 0
    enum class save_shop_type{
        none = 0,
        type_1, //1.4.0
        type_2, //1.5.0 ShopTailor + 0x18 (EventItem * 3); ShopShoes + 0x10 (EventItem * 2); ShopZakka + 0x18 (EventItem * 3);
        type_3, //1.6.0 ShopTailor + 0x50 (XmasItem * 10); ShopZakka + 0x80 (XmasItem * 16)
        type_4, //1.7.0 ShopTailor + 0x50 (CarnivalItem * 10); ShopZakka + 0x80 (CarnivalItem * 16); ShopCatalog + 0x100 (ValentineLog * 16 + ValentineItem * 16)
        type_5, //1.9.0 ShopTailor + 0x50 (PromItem * 10); ShopZakka + 0x40 (EasterItem * 8)
        type_6 //2.0.0 added ShopCommune; + 0x384
    };

    class save_shop_1 {
    protected:
        static const int size = 0x3044;
        u8 everything[size];
        save_shop_1() {}
    public:
        static int get_size() {return size;}

        virtual u8 *get_everything();

        save_shop_1(void *data);
    }; 

    class save_shop_2 : public save_shop_1 {
    protected:
        static const int size = 0x3084;
        u8 everything[size];

        save_shop_2() {}
    public:
        static int get_size() {return size;}

        u8 *get_everything() override;

        save_shop_2(void *data);

        save_shop_1 *downgrade();
    };

    class save_shop_3 : public save_shop_2 {
    protected:
        static const int size = 0x3154;
        u8 everything[size];
        save_shop_3() {}
    public:
        static int get_size() {return size;}

        u8 *get_everything() override;

        save_shop_3(void *data);

        save_shop_2 *downgrade();
    };

    class save_shop_4 : public save_shop_3 {
    protected:
        static const int size = 0x3324;
        u8 everything[size];
        save_shop_4() {}
    public:
        static int get_size() {return size;}

        u8 *get_everything() override;

        save_shop_4(void *data);

        save_shop_3 *downgrade();
    };

    class save_shop_5 : public save_shop_4 {
    protected:
        static const int size = 0x33B4;
        u8 everything[size];
        save_shop_5() {}
    public:
        static int get_size() {return size;}

        u8 *get_everything() override;

        save_shop_5(void *data);

        save_shop_4 *downgrade();
    };

    class save_shop_6 : public save_shop_5 {
    protected:
        static const int size = 0x3738;
        u8 everything[size];
    public:
        static int get_size() {return size;}

        u8 *get_everything() override;

        save_shop_6(void *data);

        save_shop_5 *downgrade();
    };

    save_shop_2 *upgrade(save_shop_1 save_shop);
    save_shop_3 *upgrade(save_shop_2 save_shop);
    save_shop_4 *upgrade(save_shop_3 save_shop);
    save_shop_5 *upgrade(save_shop_4 save_shop);
    save_shop_6 *upgrade(save_shop_5 save_shop);

    std::unique_ptr<save_shop_1 *> get_save_shop(void *data, u16 revision_in, u16 revision_out, save_shop_type &type);

}
