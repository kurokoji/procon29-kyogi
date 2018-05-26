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

#ifndef MIKURU_PROBLEM_STATE_H_
#define MIKURU_PROBLEM_STATE_H_

#include "color.h"
#include "color_field.h"
#include "field.h"
#include "types.h"
#include <array>
#include <istream>
#include <ostream>
#include <utility>

namespace mikuru {
class ProblemState {
private:
  Field field_;
  ColorField color_field_;
  std::array<std::pair<size_t, size_t>, 2> blue_, red_;

public:
  ProblemState();

  friend std::ostream& operator<<(std::ostream&, ProblemState const&);
  friend std::istream& operator>>(std::istream&, ProblemState&);
};
} // namespace mikuru

#endif
