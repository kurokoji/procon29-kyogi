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

#ifndef PROCON29_MIKURU_COLOR_FIELD_HPP_
#define PROCON29_MIKURU_COLOR_FIELD_HPP_

#include "color.hpp"
#include "field.hpp"
#include <array>

namespace mikuru {
class color_field : public field {
private:
  std::array<std::array<color, MAX_FIELD_SIZE>, MAX_FIELD_SIZE> field_;

public:
  color_field() noexcept;
  color_field(size_t, size_t) noexcept;

  friend std::ostream& operator<<(std::ostream&, color_field const&);
  friend std::istream& operator>>(std::istream&, color_field&);
};
}  // namespace mikuru

#endif
