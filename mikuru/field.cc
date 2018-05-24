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
score_type Field::at(size_t h, size_t w) const { return field_.at(h).at(w); }
score_type& Field::at(size_t h, size_t w) { return field_.at(h).at(w); }
size_t Field::height() const { return height_; }
size_t Field::width() const { return width_; }
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
void operator>>(std::istream& is, Field& field) {
  is >> field.height_ >> field.width_;
  for (size_t h = 0; h < field.height_; ++h) {
    for (size_t w = 0; w < field.width_; ++w) {
      is >> field.at(h, w);
    }
  }
}
} // namespace mikuru
