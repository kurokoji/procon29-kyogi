//====================================================
//
//  mikuru
//
//  Copyright (c) 2018 Shu Kakihana
//
//  This software is released under the MIT License.
//  https://opensource.org/licenses/mit-license.php
//
//====================================================

#include "color_field.hpp"

namespace mikuru {
/*
 * public
 */
color_field::color_field() noexcept {}
color_field::color_field(size_t h, size_t w) noexcept : field(h, w) {}
std::ostream& operator<<(std::ostream& os, color_field const& field) {
  os << field.height_ << " " << field.width_ << '\n';
  for (size_t h = 0; h < field.height_; ++h) {
    for (size_t w = 0; w < field.width_; ++w) {
      os << field.at(h, w) << (w == field.width_ - 1 ? '\n' : ' ');
    }
  }
  os.flush();
  return os;
}
std::istream& operator>>(std::istream& is, color_field& field) {
  is >> field.height_ >> field.width_;
  for (size_t h = 0; h < field.height_; ++h) {
    for (size_t w = 0; w < field.width_; ++w) {
      is >> field.at(h, w);
    }
  }
  return is;
}
} // namespace mikuru
