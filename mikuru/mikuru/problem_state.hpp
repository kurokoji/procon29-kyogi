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

#ifndef MIKURU_PROBLEM_STATE_H_
#define MIKURU_PROBLEM_STATE_H_

#include "color.hpp"
#include "color_field.hpp"
#include "field.hpp"
#include "types.hpp"
#include <array>
#include <istream>
#include <ostream>
#include <utility>

namespace mikuru {
class problem_state {
private:
  field field_;
  field color_field_;
  std::array<std::pair<size_t, size_t>, 2> blue_, red_;

public:
  problem_state();

  friend std::ostream& operator<<(std::ostream&, problem_state const&);
  friend std::istream& operator>>(std::istream&, problem_state&);
};
} // namespace mikuru

#endif
