#include "Game.hpp"
#include <HamFramework.hpp>
#include <Siv3D.hpp>  // OpenSiv3D v0.2.6

void Main() {
  Window::Resize(1280, 780);

  kyon::Game game;

  bool canStart = false;

  while (System::Update()) {
    game.getTurn();

    if (game.startGame(840, 10)) {
      canStart = true;
    }
    if (canStart) {
      game.draw();
    }

    game.finishTurn(840, 100);
    game.undo(840, 200);
  }
}
