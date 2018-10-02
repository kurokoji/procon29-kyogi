#ifndef PROCON29_KYON_GAME_HPP_
#define PROCON29_KYON_GAME_HPP_

#include <vector>
#include <array>
#include <ostream>
#include <istream>

namespace kyon {
enum class Color { None, Blue, Red };
struct ProblemState {
  using Field = std::vector<std::vector<int32>>;
  Field field;
  Field fieldColor;

  std::array<std::pair<size_t, size_t>, 2> blue, red;

  ProblemState();

  friend std::ostream& operator<<(std::ostream&, const ProblemState&);
  friend std::istream& operator>>(std::istream&, ProblemState&);
};
} // namespace kyon
