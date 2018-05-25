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
  size_t height() const;
  size_t width() const;
  score_type at(size_t, size_t) const;
  score_type& at(size_t, size_t);

  friend std::ostream& operator<<(std::ostream&, Field const&);
  friend void operator>>(std::istream&, Field&);
};
} // namespace mikuru

#endif
