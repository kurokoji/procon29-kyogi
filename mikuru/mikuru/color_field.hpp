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

#ifndef MIKURU_COLOR_FIELD_H_
#define MIKURU_COLOR_FIELD_H_

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
} // namespace mikuru

#endif
