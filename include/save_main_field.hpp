#pragma once
#include <save_struct.hpp>
#include <cstring>

namespace save_main_field {

    // enum class save_main_field_type{
    //     none = 0,
    //     type_1,
    //     type_2
    // };

    // Interface class
    class save_main_field {
    public:
        virtual u8 const *to_bin() = 0;
        virtual int get_size() = 0;

        virtual void from_data(u8 *data) = 0;

        virtual std::unique_ptr<save_main_field> upgrade() = 0;
        virtual std::unique_ptr<save_main_field> downgrade() = 0;
    };

    class save_main_field_1 : public save_main_field {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_main_field_1() = default;
        save_main_field_1(const save_main_field_1&) = default;
        save_main_field_1(save_main_field_1&&) = default;
        save_main_field_1(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_main_field> upgrade() override;
        std::unique_ptr<save_main_field> downgrade() override;
    private:
        static const int m_size = 0xDAA2C;
        u8 m_buffer[m_size];
    };

    class save_main_field_2 : public save_main_field {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        save_main_field_2() = default;
        save_main_field_2(const save_main_field_2&) = default;
        save_main_field_2(save_main_field_2&&) = default;
        save_main_field_2(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_main_field> upgrade() override;
        std::unique_ptr<save_main_field> downgrade() override;
    private:
        static const int m_size = 0xDB2CC; // AdditionalAudioInfoV = 0x20 * 69, indeed, 69
        u8 m_buffer[m_size];
    };

    std::unique_ptr<save_main_field> get_save_main_field(u8 *data, u16 revision_in, u16 revision_out);
};
