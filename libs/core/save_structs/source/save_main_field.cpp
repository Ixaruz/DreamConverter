#include "save_structs/save_main_field.hpp"

namespace save_main_field
{
    std::vector<u16> revisions =
    {
        21, //1.11.0 (revision before upgrade)
        22, //2.0.0
        31  //3.0.0
    };

    static std::map<u16, std::function<std::unique_ptr<save_main_field>(u8*)>> constructors =
    {
        {21, [](u8* data){ return std::make_unique<save_main_field_1>(data); }},
        {22, [](u8* data){ return std::make_unique<save_main_field_2>(data); }},
        {31, [](u8* data){ return std::make_unique<save_main_field_3>(data); }}
    };

    u8 const *save_main_field_1::to_bin() { return m_buffer; }
    u8 const *save_main_field_2::to_bin() { return m_buffer; }
    u8 const *save_main_field_3::to_bin() { return m_buffer; }  
    int save_main_field_1::get_size() { return m_size; }
    int save_main_field_2::get_size() { return m_size; }
    int save_main_field_3::get_size() { return m_size; }

    void save_main_field_1::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_main_field_2::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }
    void save_main_field_3::from_data (u8 *data) { memcpy(m_buffer, data, m_size); }

    save_main_field_1::save_main_field_1 (u8 *data) { this->from_data(data); }
    save_main_field_2::save_main_field_2 (u8 *data) { this->from_data(data); }
    save_main_field_3::save_main_field_3 (u8 *data) { this->from_data(data); }

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

    std::unique_ptr<save_main_field> save_main_field_3::downgrade()
    {
        save_main_field_2 *res = new save_main_field_2();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset_res = 0;
        u32 offset_in =  0;
        u64 empty_item = 0xFFFE;
        BufferConverter item_layer_converter(
            m_item_layer_layout,
            res->get_item_layer_layout(),
            PadAlign::Center,   // rows
            PadAlign::Center,   // cols
            empty_item
        );
        // ItemLayer0
        item_layer_converter.new_to_old(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_item_layer_layout.rows * m_item_layer_layout.cols * m_item_layer_layout.element_size;
        offset_res += res->get_item_layer_layout().rows * res->get_item_layer_layout().cols * res->get_item_layer_layout().element_size;
        // ItemLayer1
        item_layer_converter.new_to_old(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_item_layer_layout.rows * m_item_layer_layout.cols * m_item_layer_layout.element_size;
        offset_res += res->get_item_layer_layout().rows * res->get_item_layer_layout().cols * res->get_item_layer_layout().element_size;

        BufferConverter item_switch_converter(
            m_item_switch_layout,
            res->get_item_switch_layout(),
            PadAlign::Center,   // rows
            PadAlign::Center,   // cols
            0
        );
        // ItemSwitch0
        item_switch_converter.new_to_old(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_item_switch_layout.rows * m_item_switch_layout.cols * m_item_switch_layout.element_size;
        offset_res += res->get_item_switch_layout().rows * res->get_item_switch_layout().cols * res->get_item_switch_layout().element_size;
        // ItemSwitch1
        item_switch_converter.new_to_old(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_item_switch_layout.rows * m_item_switch_layout.cols * m_item_switch_layout.element_size;
        offset_res += res->get_item_switch_layout().rows * res->get_item_switch_layout().cols * res->get_item_switch_layout().element_size;
        // LandMakingMap is normal
        memcpy(buffer + offset_res,
            m_buffer + offset_in,
            0x24C00
            );
        offset_in  += 0x24C00;
        offset_res += 0x24C00;
        // MainFieldStructure can have 1 less structure, how fun!
        memcpy(buffer + offset_res,
            m_buffer + offset_in,
            0x398
            );
        offset_in  += 0x3AC;
        offset_res += 0x398;

        // copy everything between MainFieldStructure and MyDesignMap
        memcpy(buffer + offset_res,
            m_buffer + offset_in,
            0x9C
            );
        offset_in  += 0x9C;
        offset_res += 0x9C;

        BufferConverter design_map_converter(
            m_design_map_layout,
            res->get_design_map_layout(),
            PadAlign::Center,   // rows
            PadAlign::Center,   // cols
            0xF800
        );
        // MyDesignMap
        design_map_converter.new_to_old(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_design_map_layout.rows * m_design_map_layout.cols * m_design_map_layout.element_size;
        offset_res += res->get_design_map_layout().rows * res->get_design_map_layout().cols * res->get_design_map_layout().element_size;
        // Finally, copy the rest of the data that is unchanged
        memcpy(buffer + offset_res,
            m_buffer + offset_in,
            res->get_size() - offset_res
            );
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_main_field_2>(*(res));
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
        save_main_field_3 *res = new save_main_field_3();
        u8 *buffer = new u8[res->get_size()]{0};
        u32 offset_res = 0;
        u32 offset_in =  0;
        u64 empty_item = 0xFFFE;
        BufferConverter item_layer_converter(
            m_item_layer_layout,
            res->get_item_layer_layout(),
            PadAlign::Center,   // rows
            PadAlign::Center,   // cols
            empty_item
        );
        // ItemLayer0
        item_layer_converter.old_to_new(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_item_layer_layout.rows * m_item_layer_layout.cols * m_item_layer_layout.element_size;
        offset_res += res->get_item_layer_layout().rows * res->get_item_layer_layout().cols * res->get_item_layer_layout().element_size;
        // ItemLayer1
        item_layer_converter.old_to_new(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_item_layer_layout.rows * m_item_layer_layout.cols * m_item_layer_layout.element_size;
        offset_res += res->get_item_layer_layout().rows * res->get_item_layer_layout().cols * res->get_item_layer_layout().element_size;

        BufferConverter item_switch_converter(
            m_item_switch_layout,
            res->get_item_switch_layout(),
            PadAlign::Center,   // rows
            PadAlign::Center,   // cols
            0
        );
        // ItemSwitch0
        item_switch_converter.old_to_new(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_item_switch_layout.rows * m_item_switch_layout.cols * m_item_switch_layout.element_size;
        offset_res += res->get_item_switch_layout().rows * res->get_item_switch_layout().cols * res->get_item_switch_layout().element_size;
        // ItemSwitch1
        item_switch_converter.old_to_new(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_item_switch_layout.rows * m_item_switch_layout.cols * m_item_switch_layout.element_size;
        offset_res += res->get_item_switch_layout().rows * res->get_item_switch_layout().cols * res->get_item_switch_layout().element_size;
        // LandMakingMap is normal
        memcpy(buffer + offset_res,
            m_buffer + offset_in,
            0x24C00
            );
        offset_in  += 0x24C00;
        offset_res += 0x24C00;
        // MainFieldStructure can have 1 more structure, how fun!
        memcpy(buffer + offset_res,
            m_buffer + offset_in,
            0x398
            );
        offset_in  += 0x398;
        offset_res += 0x3AC;

        // copy everything between MainFieldStructure and MyDesignMap
        memcpy(buffer + offset_res,
            m_buffer + offset_in,
            0x9C
            );
        offset_in  += 0x9C;
        offset_res += 0x9C;

        BufferConverter design_map_converter(
            m_design_map_layout,
            res->get_design_map_layout(),
            PadAlign::Center,   // rows
            PadAlign::Center,   // cols
            0xF800
        );
        // MyDesignMap
        design_map_converter.old_to_new(
            m_buffer + offset_in,
            buffer + offset_res
        );
        offset_in  += m_design_map_layout.rows * m_design_map_layout.cols * m_design_map_layout.element_size;
        offset_res += res->get_design_map_layout().rows * res->get_design_map_layout().cols * res->get_design_map_layout().element_size;
        // Finally, copy the rest of the data that is unchanged
        memcpy(buffer + offset_res,
            m_buffer + offset_in,
            res->get_size() - offset_res
            );
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_main_field_3>(*(res));
    }

    std::unique_ptr<save_main_field> save_main_field_3::upgrade()
    {
        return std::make_unique<save_main_field_3>(*(this));
    }

    Layout save_main_field_1::get_item_layer_layout() { return m_item_layer_layout; }
    Layout save_main_field_2::get_item_layer_layout() { return m_item_layer_layout; }
    Layout save_main_field_3::get_item_layer_layout() { return m_item_layer_layout; }
    Layout save_main_field_1::get_item_switch_layout() { return m_item_switch_layout; }
    Layout save_main_field_2::get_item_switch_layout() { return m_item_switch_layout; }
    Layout save_main_field_3::get_item_switch_layout() { return m_item_switch_layout; }
    Layout save_main_field_1::get_design_map_layout() { return m_design_map_layout; }
    Layout save_main_field_2::get_design_map_layout() { return m_design_map_layout; }
    Layout save_main_field_3::get_design_map_layout() { return m_design_map_layout; }

    std::unique_ptr<save_main_field> get_save_main_field(u8 *data, u16 revision_in, u16 revision_out)
    {
        return save_struct::get_save_struct<save_main_field>(constructors,
                                                             revisions,
                                                             data,
                                                             revision_in,
                                                             revision_out);
    }
}
