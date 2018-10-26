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

#include "problem_state.hpp"
#include "color_field.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

namespace mikuru {
/*
 * public
 */

problem_state::problem_state() {}
std::ostream& operator<<(std::ostream& os, problem_state const& problem) {
  os << problem.field_;
  os << problem.color_field_;

  for (const auto& e : problem.blue_) {
    os << e.first << " " << e.second << '\n';
  }

  for (const auto& e : problem.red_) {
    os << e.first << " " << e.second << '\n';
  }

  return os;
}
std::istream& operator>>(std::istream& is, problem_state& problem) {
  is >> problem.field_;
  problem.color_field_.setHeight(problem.field_.getHeight());
  problem.color_field_.setWidth(problem.field_.getWidth());
  for (size_t i = 0; i < problem.field_.getHeight(); ++i) {
    for (size_t j = 0; j < problem.field_.getWidth(); ++j) {
      problem.color_field_.at(i, j) = 0;
    }
  }

  for (size_t i = 0; i < 2; ++i) {
    auto& [blue_h, blue_w] = problem.blue_.at(i);
    auto& [red_h, red_w] = problem.red_.at(i);
    int32 h, w;
    is >> h >> w;
    --h;
    --w;
    blue_h = static_cast<size_t>(h);
    blue_w = static_cast<size_t>(w);

    problem.color_field_.at(blue_h, blue_w) = 1;

    red_h = static_cast<size_t>(h);
    red_w = static_cast<size_t>(std::abs(
                static_cast<int32>(problem.field_.getWidth()) - w - 1)) %
            problem.field_.getWidth();

    problem.color_field_.at(red_h, red_w) = 2;
  }
  return is;
}
} // namespace mikuru
