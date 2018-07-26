#include "button.hpp"
#include <Siv3D.hpp>

int Button::click() {
  if (rect.leftClicked()) {
    clickNum++;
  }

  if (clickNum == 3) {
    clickNum = 0;
  }

  return clickNum;
}

void Button::dispSquareNum(int32 onSquareNum, int32 x, int32 y) {
  font(onSquareNum).draw(x, y, Palette::Black);
}
