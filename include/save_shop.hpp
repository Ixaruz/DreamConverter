#pragma once
#include <save_struct.hpp>
#include <cstring>

namespace save_shop {
    //can all be upgraded easily; just need to fill the gaps with empty items; except in ShopCommune, needs to be filled with 0
    // enum class save_shop_type{
    //     none = 0,
    //     type_1, //1.4.0
    //     type_2, //1.5.0 ShopTailor + 0x18 (EventItem * 3); ShopShoes + 0x10 (EventItem * 2); ShopZakka + 0x18 (EventItem * 3);
    //     type_3, //1.6.0 ShopTailor + 0x50 (XmasItem * 10); ShopZakka + 0x80 (XmasItem * 16)
    //     type_4, //1.7.0 ShopTailor + 0x50 (CarnivalItem * 10); ShopZakka + 0x80 (CarnivalItem * 16); ShopCatalog + 0x100 (ValentineLog * 16 + ValentineItem * 16)
    //     type_5, //1.9.0 ShopTailor + 0x50 (PromItem * 10); ShopZakka + 0x40 (EasterItem * 8)
    //     type_6 //2.0.0 added ShopCommune; + 0x384
    // };

    // Interface class
    class save_shop {
    public:
        virtual u8 const *to_bin() = 0;
        virtual int get_size() = 0;

        virtual void from_data(u8 *data) = 0;

        virtual std::unique_ptr<save_shop> upgrade() = 0;
        virtual std::unique_ptr<save_shop> downgrade() = 0;
    };

    class save_shop_1 : public save_shop {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_shop_1() = default;
        save_shop_1(const save_shop_1&) = default;
        save_shop_1(save_shop_1&&) = default;
        save_shop_1(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_shop> upgrade() override;
        std::unique_ptr<save_shop> downgrade() override;
    private:
        static const int m_size = 0x3044;
        u8 m_buffer[m_size];
    };

    class save_shop_2 : public save_shop {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_shop_2() = default;
        save_shop_2(const save_shop_2&) = default;
        save_shop_2(save_shop_2&&) = default;
        save_shop_2(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_shop> upgrade() override;
        std::unique_ptr<save_shop> downgrade() override;
    private:
        static const int m_size = 0x3084;
        u8 m_buffer[m_size];
    };

    class save_shop_3 : public save_shop {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_shop_3() = default;
        save_shop_3(const save_shop_3&) = default;
        save_shop_3(save_shop_3&&) = default;
        save_shop_3(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_shop> upgrade() override;
        std::unique_ptr<save_shop> downgrade() override;
    private:
        static const int m_size = 0x3154;
        u8 m_buffer[m_size];
    };

    class save_shop_4 : public save_shop {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_shop_4() = default;
        save_shop_4(const save_shop_4&) = default;
        save_shop_4(save_shop_4&&) = default;
        save_shop_4(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_shop> upgrade() override;
        std::unique_ptr<save_shop> downgrade() override;
    private:
        static const int m_size = 0x3324;
        u8 m_buffer[m_size];
    };

    class save_shop_5 : public save_shop {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_shop_5() = default;
        save_shop_5(const save_shop_5&) = default;
        save_shop_5(save_shop_5&&) = default;
        save_shop_5(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_shop> upgrade() override;
        std::unique_ptr<save_shop> downgrade() override;
    private:
        static const int m_size = 0x33B4;
        u8 m_buffer[m_size];
    };

    class save_shop_6 : public save_shop {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_shop_6() = default;
        save_shop_6(const save_shop_6&) = default;
        save_shop_6(save_shop_6&&) = default;
        save_shop_6(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_shop> upgrade() override;
        std::unique_ptr<save_shop> downgrade() override;
    private:
        static const int m_size = 0x3738;
        u8 m_buffer[m_size];
    };

    std::unique_ptr<save_shop> get_save_shop(u8 *data, u16 revision_in, u16 revision_out);
}
