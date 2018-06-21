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
#include <istream>
#include <ostream>

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
  T at(u32 h, u32 w) const { return field_.at(h).at(w); }
  T& at(u32 h, u32 w) { return field_.at(h).at(w); }

  friend std::ostream& operator<<(std::ostream& os, const field& field) {
    os << field.height_ << " " << field.width_ << '\n';
    for (u32 h = 0; h < field.height_; ++h) {
      for (u32 w = 0; w < field.width_; ++w) {
        os << field.at(h, w) << (w == field.width_ - 1 ? '\n' : ' ');
      }
    }

    return os;
  }
  friend std::istream& operator>>(std::istream& is, field& field) {
    is >> field.height_ >> field.width_;
    for (u32 h = 0; h < field.height_; ++h) {
      for (u32 w = 0; w < field.width_; ++w) {
        is >> field.at(h, w);
      }
    }

    return is;
  }
};
}  // namespace nagato

#endif
