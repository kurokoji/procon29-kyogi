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

#include "field.h"
#include "types.h"

namespace mikuru {
/*
 * public
 */

Field::Field() noexcept : height_(0), width_(0) {}
Field::Field(size_t h, size_t w) noexcept : height_(h), width_(w) {}
auto Field::at(size_t h, size_t w) const -> decltype(field_.at(h).at(w)) {
  return field_.at(h).at(w);
}
auto Field::at(size_t h, size_t w) -> decltype(field_.at(h).at(w))& {
  return field_.at(h).at(w);
}
size_t Field::getHeight() const { return height_; }
size_t Field::getWidth() const { return width_; }
std::ostream& operator<<(std::ostream& os, Field const& field) {
  os << field.height_ << " " << field.width_ << '\n';
  for (size_t h = 0; h < field.height_; ++h) {
    for (size_t w = 0; w < field.width_; ++w) {
      os << field.at(h, w) << (w == field.width_ - 1 ? '\n' : ' ');
    }
  }
  os.flush();
  return os;
}
std::istream& operator>>(std::istream& is, Field& field) {
  is >> field.height_ >> field.width_;
  for (size_t h = 0; h < field.height_; ++h) {
    for (size_t w = 0; w < field.width_; ++w) {
      is >> field.at(h, w);
    }
  }
  return is;
}
} // namespace mikuru
