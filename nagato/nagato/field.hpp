//====================================================
//
//  nagato
//
//  Copyright (c) 2018 Shu Kakihana
//
//  This software is released under the GNU General Public License version 3.
//  https://opensource.org/licenses/GPL-3.0
//
//====================================================

#ifndef NAGATO_FIELD_HPP_
#define NAGATO_FIELD_HPP_

#include "types.hpp"
#include <array>

namespace nagato {
template <typename T>
class field {
protected:
  static constexpr u32 MAX_FIELD_SIZE = 12;
  u32 height_, width_;

private:
  std::array<std::array<T, MAX_FIELD_SIZE>, MAX_FIELD_SIZE> field_;

public:
  field() noexcept : height_(0), width_(0) {}
  field(u32 h, u32 w) noexcept : height_(h), width_(w) {}
  u32 get_height() const { return height_; }
  u32 get_width() const { return width_; }
};
}  // namespace nagato

#endif
