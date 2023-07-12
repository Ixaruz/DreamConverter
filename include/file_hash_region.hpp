#pragma once
#include <types.hpp>

class file_hash_region
{
public:
    u32 hash_offset;
    u32 size;
    u32 get_begin_offset() const { return hash_offset + 4; }
    u32 get_end_offset() const { return get_begin_offset() + size; }

    file_hash_region(u32 hashOfs, u32 Size) : hash_offset(hashOfs), size(Size)
    {}
};
