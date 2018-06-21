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

#ifndef PROCON29_MIKURU_FIELD_HPP_
#define PROCON29_MIKURU_FIELD_HPP_

#include "types.hpp"
#include <array>
#include <istream>
#include <ostream>

namespace mikuru {
class field {
protected:
  static size_t constexpr MAX_FIELD_SIZE = 12;
  size_t height_, width_;

private:
  std::array<std::array<score_type, MAX_FIELD_SIZE>, MAX_FIELD_SIZE> field_;

public:
  field() noexcept;
  field(size_t, size_t) noexcept;
  size_t getHeight() const;
  size_t getWidth() const;
  auto at(size_t h, size_t w) const -> decltype(field_.at(h).at(w));
  auto at(size_t h, size_t w) -> decltype(field_.at(h).at(w))&;

  friend std::ostream& operator<<(std::ostream&, field const&);
  friend std::istream& operator>>(std::istream&, field&);
};
}  // namespace mikuru

#endif
