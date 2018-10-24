#ifndef PROCON29_MOVE_DATA_HPP_
#define PROCON29_MOVE_DATA_HPP_

#include <array>

#include <Siv3D.hpp>

namespace kyon {
struct MoveData {
  Array<int32> blue, red;

  MoveData();

  std::string to_string();
  friend std::ostream& operator<<(std::ostream&, const MoveData&);
  friend std::istream& operator>>(std::istream&, MoveData&);
};
}

#endif
