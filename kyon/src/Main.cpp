#include "Game.hpp"
#include <HamFramework.hpp>
#include <Siv3D.hpp>  // OpenSiv3D v0.2.6

void Main() {
  Window::Resize(1280, 780);

  // 画面遷移のマネージャー
  kyon::App manager;
  manager.setFadeColor(ColorF(1.0, 1.0, 1.0));
  manager.add<kyon::Game>(U"Game");

  const Font font(50);

  while (System::Update()) {
    if (!manager.update()) {
      break;
    }
  }
}
