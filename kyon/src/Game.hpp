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
#include "CommandGUI.hpp"

namespace kyon {

class Game {
public:
  ProblemState problemState;
  Field field;
  SolverAnswer solverAnswer;

  Button TurnFinish;
  Button startButton;
  Button undoButton;
  Button enterButton;
  Button toggleColorButton;
  Font turnNum;
  Font pointSumLabel;
  Font turnLabel;
  TextBox inputTurn;
  String nowTurn;
  String maxTurn;
  CommandGUI cmdGUI;

  Game();
  bool getInformation();
  void update();
  void draw();
  std::string getFieldData();
  SolverAnswer getSolverAnswer();
  void getTurnData();
  void postMoveData();
  void postTurnData();
  bool startGame(int32 x, int32 y);
  void finishTurn(int32 x, int32 y);
  void undo(int32 x, int32 y);
  void toggleColor(int32 x, int32 y);
  void pointSum(int32 x, int32 y);
  void dispTurn(int32 x, int32 y);
  void getTurn();
};

} // namespace kyon

#endif
