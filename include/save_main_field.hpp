#pragma once
#include <types.hpp>
#include <cstring>
#include <memory>

namespace save_main_field {

    enum class save_main_field_type{
        none = 0,
        type_1,
        type_2
    };

    class save_main_field_1 {
    protected:
        static const int size = 0xDAA2C;
        u8 everything[size];
        save_main_field_1() {}
    public:
        static int get_size() {return size;}

        virtual u8 *get_everything();

        save_main_field_1(void *data);
    }; 

    class save_main_field_2 : public save_main_field_1 {
    protected:
        static const int size = 0xDB2CC;
        u8 everything[size];
        u8 AdditionalAudioInfoV[0x20 * 69]; //indeed, 69
    public:
        static int get_size() {return size;}

        u8 *get_everything() override;

        save_main_field_2(void *data);

        save_main_field_1 *downgrade();
    };

    save_main_field_2 *upgrade(save_main_field_1 save_main_field);

    std::unique_ptr<save_main_field_1 *> get_save_main_field(void *data, u16 revision_in, u16 revision_out, save_main_field_type &type);
};