#pragma once
#include <cstddef>
#include <cstdint>

enum class PadAlign {
    Start,   // top or left
    End,     // bottom or right
    Center
};

struct Layout {
    size_t element_size; // bytes per element
    size_t rows;         // number of rows
    size_t cols;         // number of elements per row
};

class BufferConverter {
public:
    BufferConverter(
        Layout old_layout,
        Layout new_layout,
        PadAlign row_align,
        PadAlign col_align,
        uint64_t pad_value = 0
    );

    void old_to_new(const void* old_buf, void* new_buf) const;
    void new_to_old(const void* new_buf, void* old_buf) const;

private:
    Layout   old_;
    Layout   new_;
    PadAlign row_align_;
    PadAlign col_align_;
    uint64_t pad_value_;

    static size_t aligned_offset(
        size_t used,
        size_t total,
        PadAlign align
    );

    void convert(
        const void* src,
        void* dst,
        const Layout& src_l,
        const Layout& dst_l,
        bool pad
    ) const;
};
