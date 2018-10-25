#include "Game.hpp"
#include <HamFramework.hpp>
#include <Siv3D.hpp>  // OpenSiv3D v0.2.6

void Main() {
  Window::Resize(1280, 780);

  kyon::Game game;
  kyon::Button start(90, 60, 45, U"始");

  start.setPos(840, 10);
  bool canStart = false;


  const Font font(50);

  while (System::Update()) {

    start.draw();

    if (start.isClick()) {
      game.getInformation();
      canStart = true;
    }
    if (canStart) {
      game.draw();
    }
    game.finishTurn(840, 100);
  }
}
