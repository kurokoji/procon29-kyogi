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
class ColorField : public Field {
private:
  std::array<std::array<Color, MAX_FIELD_SIZE>, MAX_FIELD_SIZE> field_;

public:
  ColorField() noexcept;
  ColorField(size_t, size_t) noexcept;

  friend std::ostream& operator<<(std::ostream&, ColorField const&);
  friend std::istream& operator>>(std::istream&, ColorField&);
};
} // namespace mikuru

#endif
