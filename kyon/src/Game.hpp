#ifndef PROCON29_KYON_GAME_HPP_
#define PROCON29_KYON_GAME_HPP_

#include <Siv3D.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <array>
#include <boost/asio.hpp>
#include "Button.hpp"
#include "FieldSquare.hpp"
#include "ProblemState.hpp"

namespace kyon {

class Game {
public:
//  ProblemState problemState;
  FieldSquare fs {0, U"1"};

  Game();

  void update();
  void draw();
  String getFieldData();
  std::tuple<int32, int32, Array<Array<int32>>, std::array<std::pair<size_t, size_t>, 4>> parseFieldData(const String &fieldData);
};

}  // namespace kyon

#endif
