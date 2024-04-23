#include <save_main_field.hpp>
namespace save_main_field {
    u8 *save_main_field_1::get_everything() {return everything;}

    save_main_field_1::save_main_field_1(void *data){
        memcpy(everything, data, size);
    }

    u8 * save_main_field_2::get_everything() {
        u8 *buffer = new u8[size]{0};
        memcpy(buffer, everything, 0xDAA2C);
        memcpy(buffer + 0xDAA2C, AdditionalAudioInfoV, 0x20 * 69);
        return buffer;
    }

    save_main_field_2::save_main_field_2(void *data){
        memcpy(everything, data, save_main_field_1::get_size());
        memcpy(AdditionalAudioInfoV, (u8 *)data + save_main_field_1::get_size(), 0x20 * 69);
    }

    save_main_field_1 *save_main_field_2::downgrade(){
        return new save_main_field_1(everything);
    }

    save_main_field_2 *upgrade(save_main_field_1 save_main_field){
        u8 *buffer = new u8[save_main_field_2::get_size()]{0};
        memcpy(buffer, save_main_field.get_everything(), save_main_field_2::get_size());
        save_main_field_2 *res = new save_main_field_2(buffer);
        delete buffer;
        return res;
    }

    std::unique_ptr<save_main_field_1 *> get_save_main_field(void *data, u16 revision_in, u16 revision_out, save_main_field_type &type) {
        switch(revision_out) {
            case 0 ... 21:
            {
                type = save_main_field_type::type_1;
                switch(revision_in) {
                    case 0 ... 21:
                        return std::make_unique<save_main_field_1 *>(new save_main_field_1(data));
                    case 22 ... 28:
                        return std::make_unique<save_main_field_1 *>(save_main_field_2(data).downgrade());
                    default: 
                        break;
                }
            }
            case 22 ... 28:
            {
                type = save_main_field_type::type_2;
                switch(revision_in) {
                    case 0 ... 21:
                        return std::make_unique<save_main_field_1 *>(upgrade(save_main_field_1(data)));
                    case 22 ... 28:
                        return std::make_unique<save_main_field_1 *>(new save_main_field_2(data));
                    default: 
                        break;
                }
            }
            default:
                type = save_main_field_type::none;
                return std::make_unique<save_main_field_1 *>(nullptr);
        }
    }
}