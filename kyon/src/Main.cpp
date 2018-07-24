#include "Game.hpp"
#include <Siv3D.hpp> // OpenSiv3D v0.2.6
#include <HamFramework.hpp>

void Main() {
    // 画面遷移のマネージャー
    App manager;
    manager.setFadeColor(ColorF(1.0, 1.0, 1.0));
    manager.add<Game>(U"Game");

    const Font font(50);

    while (System::Update()) {
        if (!manager.update()) {
            break;
        }
    }
}
