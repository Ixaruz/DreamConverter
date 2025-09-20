#pragma once
#include "save_struct.hpp"

#include <cstring>

namespace save_land_my_design {

    // enum class save_land_my_design_type{
    //     none = 0,
    //     type_1,
    //     type_2 // 1.9.0
    // };

    // Interface class
    class save_land_my_design {
    public:
        virtual u8 const *to_bin() = 0;
        virtual int get_size() = 0;

        virtual u8 const *get_MyDesignNormals() = 0;
        virtual u8 const *get_MyDesignPros() = 0;
        virtual u8 const *get_FlagMyDesign() = 0;
        virtual u8 const *get_TailorMyDesigns() = 0;
        virtual u8 const *get_ExhibitAccounts() = 0;

        virtual void from_data(u8 *data) = 0;

        virtual std::unique_ptr<save_land_my_design> upgrade() = 0;
        virtual std::unique_ptr<save_land_my_design> downgrade() = 0;
    };

    class save_land_my_design_1 : public save_land_my_design {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        u8 const *get_MyDesignNormals() override;
        u8 const *get_MyDesignPros() override;
        u8 const *get_FlagMyDesign() override;
        u8 const *get_TailorMyDesigns() override;
        u8 const *get_ExhibitAccounts() override;

        save_land_my_design_1() = default;
        save_land_my_design_1(const save_land_my_design_1&) = default;
        save_land_my_design_1(save_land_my_design_1&&) = default;
        save_land_my_design_1(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_land_my_design> upgrade() override;
        std::unique_ptr<save_land_my_design> downgrade() override;
    private:
        static const int m_size = 0x27E08;
        u8 m_MyDesignNormals[0x2A8 * 50];
        u8 m_MyDesignPros[0x8A8 * 50];
        u8 m_FlagMyDesign[0x2A8];
        u8 m_TailorMyDesigns[0x8A8 * 8];
        u8 m_ExhibitAccounts[0x10 * 8];
    };

    class save_land_my_design_2 : public save_land_my_design {
    protected:
    public:
        u8 const *to_bin() override;
        int get_size() override;

        u8 const *get_MyDesignNormals() override;
        u8 const *get_MyDesignPros() override;
        u8 const *get_FlagMyDesign() override;
        u8 const *get_TailorMyDesigns() override;
        u8 const *get_ExhibitAccounts() override;

        save_land_my_design_2() = default;
        save_land_my_design_2(const save_land_my_design_2&) = default;
        save_land_my_design_2(save_land_my_design_2&&) = default;
        save_land_my_design_2(u8 *data);
        void from_data(u8 *data) override;

        std::unique_ptr<save_land_my_design> upgrade() override;
        std::unique_ptr<save_land_my_design> downgrade() override;
    private:
        static const int m_size = 0x4B3A8;
        u8 m_MyDesignNormals[0x2A8 * 100];
        u8 m_MyDesignPros[0x8A8 * 100];
        u8 m_FlagMyDesign[0x2A8];
        u8 m_TailorMyDesigns[0x8A8 * 8];
        u8 m_ExhibitAccounts[0x10 * 8];
    };

    std::unique_ptr<save_land_my_design> get_save_land_my_design(u8 *data, u16 revision_in, u16 revision_out);
};
