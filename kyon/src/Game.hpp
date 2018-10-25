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
#include "SolverAnswer.hpp"

namespace kyon {

class Game {
public:
  ProblemState problemState;
  Field field;
  Button TurnFinish;
  Button startButton;
  Button undoButton;

  Game();
  void getInformation();
  void update();
  void draw();
  std::string getFieldData();
  SolverAnswer getSolverAnswer();
  void postMoveData();
  bool startGame(int32 x, int32 y);
  void finishTurn(int32 x, int32 y);
  void undo(int32 x, int32 y);
};

}  // namespace kyon

#endif
