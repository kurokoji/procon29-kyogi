#include "Game.hpp"
#include <HamFramework.hpp>
#include <Siv3D.hpp>  // OpenSiv3D v0.2.6

void Main() {
  Window::Resize(1280, 780);

  kyon::Game game;

  const Font font(50);

  while (System::Update()) {
      game.draw();
  }
}
