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

#ifndef MIKURU_FIELD_H_
#define MIKURU_FIELD_H_

#include "types.h"
#include <array>
#include <istream>
#include <ostream>

namespace mikuru {
class Field {
protected:
  static size_t constexpr MAX_FIELD_SIZE = 12;
  size_t height_, width_;

private:
  std::array<std::array<score_type, MAX_FIELD_SIZE>, MAX_FIELD_SIZE> field_;

public:
  Field() noexcept;
  Field(size_t, size_t) noexcept;
  size_t getHeight() const;
  size_t getWidth() const;
  auto at(size_t h, size_t w) const -> decltype(field_.at(h).at(w));
  auto at(size_t h, size_t w) -> decltype(field_.at(h).at(w))&;

  friend std::ostream& operator<<(std::ostream&, Field const&);
  friend std::istream& operator>>(std::istream&, Field&);
};
} // namespace mikuru

#endif
