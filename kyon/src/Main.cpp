#include "Game.hpp"
#include <HamFramework.hpp>
#include <Siv3D.hpp>  // OpenSiv3D v0.2.6

void Main() {
  Window::Resize(1280, 780);

  Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

  kyon::Game game;

  bool canStart = false;
  bool dispStartButton = true;

  while (System::Update()) {
    Profiler::EnableAssetCreationWarning(false);
    game.getTurn();

    if (dispStartButton) {
      if (game.startGame(840, 10)) {
        canStart = true;
        dispStartButton = false;
      }
    }

    if (canStart) {
      game.draw();
      game.pointSum(970, 100);
    }

    game.finishTurn(840, 100);
    game.undo(840, 200);
    game.toggleColor(840, 300);
    game.dispTurn(940, 300);
  }
}
