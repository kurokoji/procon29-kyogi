#ifndef PROCON29_MOVE_DATA_HPP_
#define PROCON29_MOVE_DATA_HPP_

#include <array>

#include <Siv3D.hpp>

namespace kyon {
struct MoveData {
  std::array<std::pair<int32, int32>, 2> blue, red;

  MoveData();

  std::string to_string();
  friend std::ostream& operator<<(std::ostream&, const MoveData&);
  friend std::istream& operator>>(std::istream&, MoveData&);
};
}

#endif
