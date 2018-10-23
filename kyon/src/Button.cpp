#include "Button.hpp"
#include <Siv3D.hpp>


namespace kyon {
Button::Button() : rect(0, 0, 60, 60), pos(60, 60), clickNum(0) {}

Button::Button(uint32 h, uint32 w, uint32 fontSize, String str) : rect(0, 0, h, w), font(fontSize), pos(h, w), rectStr(str) {}

//座標設定
Button& Button::setPos(uint32 x, uint32 y) {
  pos = Vec2(x, y);
  rect.setPos(x, y);
  return *this;
}

//マスの描画
Button& Button::draw(const String& str) {
  if (clickNum == 0) {
    rect.draw(Palette::White);
  } else if (clickNum == 1) {
    rect.draw(Palette::Red);
  } else if (clickNum == 2){
    rect.draw(Palette::Blue);
  }
  font(str).draw(pos, Palette::Black);
  return *this;
}

Button& Button::draw() {
  rect.draw(Palette::White);
  font(rectStr).draw(pos, Palette::Black);

  return *this;
}

//クリックした際の挙動
bool Button::isClick() {
  if (rect.leftClicked()) {
    return true;
  } else {
    return false;
  }
}
void Button::update() {
  if (rect.leftClicked()) {
    clickNum = (clickNum + 1) % 3;
  }
}
}
