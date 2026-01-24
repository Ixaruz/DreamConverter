#include "save_structs/buffer_converter.hpp"
#include <cstring>
#include <algorithm>
#include <cassert>

BufferConverter::BufferConverter(
    Layout old_layout,
    Layout new_layout,
    PadAlign row_align,
    PadAlign col_align,
    uint64_t pad_value
)
    : old_(old_layout),
      new_(new_layout),
      row_align_(row_align),
      col_align_(col_align),
      pad_value_(pad_value)
{
}

size_t BufferConverter::aligned_offset(
    size_t used,
    size_t total,
    PadAlign align
) {
    if (total <= used)
        return 0;

    const size_t diff = total - used;

    switch (align) {
    case PadAlign::Start:  return 0;
    case PadAlign::End:    return diff;
    case PadAlign::Center: return diff / 2;
    }
    return 0;
}

void BufferConverter::old_to_new(
    const void* old_buf,
    void* new_buf
) const {
    convert(old_buf, new_buf, old_, new_, true);
}

void BufferConverter::new_to_old(
    const void* new_buf,
    void* old_buf
) const {
    convert(new_buf, old_buf, new_, old_, false);
}

void BufferConverter::convert(
    const void* src,
    void* dst,
    const Layout& src_l,
    const Layout& dst_l,
    bool pad
) const {
    assert(src_l.element_size == dst_l.element_size);

    const size_t elem_size = src_l.element_size;

    const size_t rows = std::min(src_l.rows, dst_l.rows);
    const size_t cols = std::min(src_l.cols, dst_l.cols);

    const size_t src_row_bytes = src_l.cols * elem_size;
    const size_t dst_row_bytes = dst_l.cols * elem_size;

    const uint8_t* s = static_cast<const uint8_t*>(src);
    uint8_t*       d = static_cast<uint8_t*>(dst);

    // pad destination first
    if (pad) {
        for (size_t i = 0; i < dst_l.rows * dst_l.cols; ++i) {
            std::memcpy(
                d + i * elem_size,
                &pad_value_,
                elem_size
            );
        }
    }

    const size_t r_src = aligned_offset(rows, src_l.rows, row_align_);
    const size_t c_src = aligned_offset(cols, src_l.cols, col_align_);

    const size_t r_dst = aligned_offset(rows, dst_l.rows, row_align_);
    const size_t c_dst = aligned_offset(cols, dst_l.cols, col_align_);

    for (size_t r = 0; r < rows; ++r) {
        std::memcpy(
            d + (r + r_dst) * dst_row_bytes + c_dst * elem_size,
            s + (r + r_src) * src_row_bytes + c_src * elem_size,
            cols * elem_size
        );
    }
}
