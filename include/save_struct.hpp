#pragma once
#include <types.hpp>
#include <memory>
#include <functional>
#include <vector>
#include <map>

#ifndef SAVE_STRUCT_HPP
#define SAVE_STRUCT_HPP

namespace save_struct {

    // // Interface class
    // template <class T>
    // class save_struct {
    // protected:
    // public:
    //     virtual u8 const *to_bin() = 0;
    //     virtual int get_size() = 0;

    //     virtual void from_data(u8 *data) = 0;

    //     virtual std::unique_ptr<T> upgrade() = 0;
    //     virtual std::unique_ptr<T> downgrade() = 0;
    // };

    //expect sorted vector
    u16 get_clamped_revision(std::vector<u16> const& vec, u16 revision);

    int count_upgrades(std::vector<u16> const& vec, u16 revision_in, u16 revision_out);

    template<class T>
    std::unique_ptr<T> create_save_struct(std::map<u16, std::function<std::unique_ptr<T>(u8*)>> constructors,
                                          u8* data,
                                          u16 revision);

    template<class T>
    std::unique_ptr<T> get_save_struct(std::map<u16, std::function<std::unique_ptr<T>(u8*)>> constructors,
                                       std::vector<u16> const& revisions,
                                       u8 *data,
                                       u16 revision_in,
                                       u16 revision_out);

}

// include our template "definitions"
#include <save_struct.inl>

#endif
