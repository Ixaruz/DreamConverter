#include <save_land_my_design.hpp>

namespace save_land_my_design
{

    std::vector<u16> revisions =
    {
        17, //1.8.0 (revision before upgrade)
        18 //1.9.0
    };

    static std::map<u16, std::function<std::unique_ptr<save_land_my_design>(u8*)>> constructors =
    {
        {17, [](u8* data){ return std::make_unique<save_land_my_design_1>(data); }},
        {18, [](u8* data){ return std::make_unique<save_land_my_design_2>(data); }}
    };

    u8 const *save_land_my_design_1::to_bin()
    {
        u8 *buffer = new u8[m_size]{0};
        memcpy(buffer, m_MyDesignNormals, 0x2A8 * 50);
        u32 offset = 0x2A8 * 50;
        memcpy(buffer + offset, m_MyDesignPros, 0x8A8 * 50);
        offset += 0x8A8 * 50;
        memcpy(buffer + offset, m_FlagMyDesign, 0x2A8);
        offset += 0x2A8;
        memcpy(buffer + offset, m_TailorMyDesigns, 0x8A8 * 8);
        offset += 0x8A8 * 8;
        memcpy(buffer + offset, m_ExhibitAccounts, 0x10 * 8);
        return buffer;
    }

    u8 const *save_land_my_design_2::to_bin()
    {
        u8 *buffer = new u8[0x4B3A8]{0};
        memcpy(buffer, m_MyDesignNormals, 0x2A8 * 100);
        u32 offset = 0x2A8 * 100;
        memcpy(buffer + offset, m_MyDesignPros, 0x8A8 * 100);
        offset += 0x8A8 * 100;
        memcpy(buffer + offset, m_FlagMyDesign, 0x2A8);
        offset += 0x2A8;
        memcpy(buffer + offset, m_TailorMyDesigns, 0x8A8 * 8);
        offset += 0x8A8 * 8;
        memcpy(buffer + offset, m_ExhibitAccounts, 0x10 * 8);
        return buffer;
    }

    int save_land_my_design_1::get_size() { return m_size; }
    int save_land_my_design_2::get_size() { return m_size; }

    u8 const *save_land_my_design_1::get_MyDesignNormals() { return m_MyDesignNormals; }
    u8 const *save_land_my_design_1::get_MyDesignPros() { return m_MyDesignPros; }
    u8 const *save_land_my_design_1::get_FlagMyDesign() { return m_FlagMyDesign; }
    u8 const *save_land_my_design_1::get_TailorMyDesigns() { return m_TailorMyDesigns; }
    u8 const *save_land_my_design_1::get_ExhibitAccounts() { return m_ExhibitAccounts; }

    u8 const *save_land_my_design_2::get_MyDesignNormals() { return m_MyDesignNormals; }
    u8 const *save_land_my_design_2::get_MyDesignPros() { return m_MyDesignPros; }
    u8 const *save_land_my_design_2::get_FlagMyDesign() { return m_FlagMyDesign; }
    u8 const *save_land_my_design_2::get_TailorMyDesigns() { return m_TailorMyDesigns; }
    u8 const *save_land_my_design_2::get_ExhibitAccounts() { return m_ExhibitAccounts; }

    void save_land_my_design_1::from_data(u8 *data)
    {
        memcpy(m_MyDesignNormals, (u8 *)data, 0x2A8 * 50);
        u32 offset = 0x2A8 * 50;
        memcpy(m_MyDesignPros, (u8 *)data + offset, 0x8A8 * 50);
        offset += 0x8A8 * 50;
        memcpy(m_FlagMyDesign, (u8 *)data + offset, 0x2A8);
        offset += 0x2A8;
        memcpy(m_TailorMyDesigns, (u8 *)data + offset, 0x8A8 * 8);
        offset += 0x8A8 * 8;
        memcpy(m_ExhibitAccounts, (u8 *)data + offset, 0x10 * 8);
    }

    void save_land_my_design_2::from_data(u8 *data)
    {
        memcpy(m_MyDesignNormals, data, 0x2A8 * 100);
        u32 offset = 0x2A8 * 100;
        memcpy(m_MyDesignPros, (u8 *)data + offset, 0x8A8 * 100);
        offset += 0x8A8 * 100;
        memcpy(m_FlagMyDesign, (u8 *)data + offset, 0x2A8);
        offset += 0x2A8;
        memcpy(m_TailorMyDesigns, (u8 *)data + offset, 0x8A8 * 8);
        offset += 0x8A8 * 8;
        memcpy(m_ExhibitAccounts, (u8 *)data + offset, 0x10 * 8);
    }

    save_land_my_design_1::save_land_my_design_1(u8 *data) { this->from_data(data); }
    save_land_my_design_2::save_land_my_design_2(u8 *data) { this->from_data(data); }

    std::unique_ptr<save_land_my_design> save_land_my_design_1::downgrade()
    {
        return std::make_unique<save_land_my_design_1>(*(this));
    }

    std::unique_ptr<save_land_my_design> save_land_my_design_2::downgrade()
    {
        save_land_my_design_1 *res = new save_land_my_design_1();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_MyDesignNormals, 0x2A8 * 50);
        u32 offset = 0x2A8 * 50;
        memcpy(buffer + offset, m_MyDesignPros, 0x8A8 * 50);
        offset += 0x8A8 * 50;
        memcpy(buffer + offset, m_FlagMyDesign, 0x2A8);
        offset += 0x2A8;
        memcpy(buffer + offset, m_TailorMyDesigns, 0x8A8 * 8);
        offset += 0x8A8 * 8;
        memcpy(buffer + offset, m_ExhibitAccounts, 0x10 * 8);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_land_my_design_1>(*(res));
    }

    std::unique_ptr<save_land_my_design> save_land_my_design_1::upgrade()
    {
        save_land_my_design_2 *res = new save_land_my_design_2();
        u8 *buffer = new u8[res->get_size()]{0};
        memcpy(buffer, m_MyDesignNormals, 0x2A8 * 50);
        u32 offset = 0x2A8 * 50;
        u8 emptyDesign[0x2A8];
        //copy the last Design 50 times bc im lazy
        memcpy(emptyDesign, m_MyDesignNormals + (0x2A8 * 49), 0x2A8);
        for (int i = 0; i < 50; i++)
        {
            memcpy((u8 *)buffer + offset, emptyDesign, 0x2A8);
            offset += 0x2A8;
        }
        memcpy((u8 *)buffer + offset, m_MyDesignPros, 0x8A8 * 50);
        offset += 0x8A8 * 50;
        u8 emptyProDesign[0x8A8];
        //copy the last Design 50 times bc im lazy
        memcpy(emptyProDesign, m_MyDesignPros + (0x8A8 * 49), 0x8A8);
        for (int i = 0; i < 50; i++)
        {
            memcpy((u8 *)buffer + offset, emptyProDesign, 0x8A8);
            offset += 0x8A8;
        }
        memcpy((u8 *)buffer + offset, m_FlagMyDesign, 0x2A8);
        offset += 0x2A8;
        memcpy((u8 *)buffer + offset, m_TailorMyDesigns, 0x8A8 * 8);
        offset += 0x8A8 * 8;
        memcpy((u8 *)buffer + offset, m_ExhibitAccounts, 0x10 * 8);
        res->from_data(buffer);
        delete buffer;
        return std::make_unique<save_land_my_design_2>(*(res));
    }

    std::unique_ptr<save_land_my_design> save_land_my_design_2::upgrade()
    {
        return std::make_unique<save_land_my_design_2>(*(this));
    }


    std::unique_ptr<save_land_my_design> get_save_land_my_design(u8 *data, u16 revision_in, u16 revision_out)
    {
        return save_struct::get_save_struct<save_land_my_design>(constructors,
                                                                 revisions,
                                                                 data,
                                                                 revision_in,
                                                                 revision_out);
    }
}
