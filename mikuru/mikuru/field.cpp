//====================================================
//
//  mikuru
//
//  Copyright (c) 2018 Shu Kakihana
//
//  This software is released under the GNU General Public License version 3.
//  https://opensource.org/licenses/GPL-3.0
//
//====================================================

#include "field.hpp"
#include "types.hpp"

namespace mikuru {
/*
 * public
 */

field::field() noexcept : height_(0), width_(0) {}
field::field(size_t h, size_t w) noexcept : height_(h), width_(w) {}
auto field::at(size_t h, size_t w) const -> decltype(field_.at(h).at(w)) {
  return field_.at(h).at(w);
}
auto field::at(size_t h, size_t w) -> decltype(field_.at(h).at(w))& {
  return field_.at(h).at(w);
}
size_t field::getHeight() const { return height_; }
size_t field::getWidth() const { return width_; }
void field::setHeight(size_t h) { height_ = h; }
void field::setWidth(size_t w) { width_ = w; }
std::ostream& operator<<(std::ostream& os, field const& field) {
  os << field.height_ << " " << field.width_ << '\n';
  for (size_t h = 0; h < field.height_; ++h) {
    for (size_t w = 0; w < field.width_; ++w) {
      os << field.at(h, w) << (w == field.width_ - 1 ? '\n' : ' ');
    }
  }
  os.flush();
  return os;
}
std::istream& operator>>(std::istream& is, field& field) {
  is >> field.height_ >> field.width_;
  for (size_t h = 0; h < field.height_; ++h) {
    for (size_t w = 0; w < field.width_; ++w) {
      is >> field.at(h, w);
    }
  }
  return is;
}
} // namespace mikuru
