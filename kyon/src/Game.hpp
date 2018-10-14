#ifndef PROCON29_KYON_GAME_HPP_
#define PROCON29_KYON_GAME_HPP_

#include <Siv3D.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <boost/asio.hpp>
#include "button.hpp"
#include "fieldSquare.hpp"

namespace kyon {

class Game {
public:
  Game() {}

  void update();
  void draw();
  String getFieldData();
  std::tuple<int32, int32, std::vector<std::vector<int32>>> parseFieldData(const String &fieldData);
};

}  // namespace kyon

#endif
