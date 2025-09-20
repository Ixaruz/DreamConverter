#include "save_structs/save_main_field.hpp"

namespace save_main_field
{
    std::vector<u16> revisions =
    {
        21, //1.11.0 (revision before upgrade)
        22 //2.0.0
    };

    static std::map<u16, std::function<std::unique_ptr<save_main_field>(u8*)>> constructors =
    {
        {21, [](u8* data){ return std::make_unique<save_main_field_1>(data); }},
        {22, [](u8* data){ return std::make_unique<save_main_field_2>(data); }}
    };

    u8 const *save_main_field_1::to_bin() { return m_buffer; }
    u8 const *save_main_field_2::to_bin() { return m_buffer; }

    int save_main_field_1::get_size() { return m_size; }
    int save_main_field_2::get_size() { return m_size; }

    void save_main_field_1::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_main_field_2::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }

    save_main_field_1::save_main_field_1 (u8 *data) { this->from_data(data); }
    save_main_field_2::save_main_field_2 (u8 *data) { this->from_data(data); }

    std::unique_ptr<save_main_field> save_main_field_1::downgrade()
    {
        return std::make_unique<save_main_field_1>(*(this));
    }

    std::unique_ptr<save_main_field> save_main_field_2::downgrade()
    {
        save_main_field_1 *res = new save_main_field_1();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_buffer, res->get_size());
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_main_field_1>(*(res));
    }
    std::unique_ptr<save_main_field> save_main_field_1::upgrade(){
        save_main_field_2 *res = new save_main_field_2();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_buffer, m_size);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_main_field_2>(*(res));
    }

    std::unique_ptr<save_main_field> save_main_field_2::upgrade()
    {
        return std::make_unique<save_main_field_2>(*(this));
    }

    std::unique_ptr<save_main_field> get_save_main_field(u8 *data, u16 revision_in, u16 revision_out)
    {
        return save_struct::get_save_struct<save_main_field>(constructors,
                                                             revisions,
                                                             data,
                                                             revision_in,
                                                             revision_out);
    }
}
