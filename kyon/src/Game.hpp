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
  Button TurnFinish;

  Game();
  void getInformation();
  void update();
  void draw();
  void finishTurn(int32 x, int32 y);
  std::string getFieldData();
};

}  // namespace kyon

#endif
