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
#include "Field.hpp"
#include "ProblemState.hpp"

namespace kyon {

class Game {
public:
  ProblemState problemState;
  Field field;

  Game();

  void update();
  void draw();
  std::string getFieldData();
};

}  // namespace kyon

#endif
