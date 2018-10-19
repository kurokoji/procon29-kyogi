#include "TurnFinish.hpp"

namespace kyon {

FinishButton::FinishButton() {
  finishRect = Rect(0, 0, 100, 100);
  choice[0] = Rect(0, 0, 40, 40);
  choice[1] = Rect(0, 0, 40, 40);
  ok = Font(20);
  no = Font(20);
  moveNum = 0;
  dispChoice = false;
}

FinishButton& FinishButton::setPos(int32 x, int32 y) {
  okPos = Vec2(x + 105, y);
  noPos = Vec2(x + 105, y + 60);
  choice[0].setPos(x + 100, y);
  choice[1].setPos(x + 100, y + 60);

  finishRect.setPos(x, y);

  return* this;
}

bool FinishButton::draw() {
  finishRect.draw(Palette::White);

  if (finishRect.leftClicked()) {
    if (moveNum == 4) {
      return true;
    }
    else {
      dispChoice = true;
    }
  }

  if (dispChoice) {
    choice[1].draw(Palette::White).drawFrame(5, 0, Palette::Yellow);
    choice[0].draw(Palette::White).drawFrame(5, 0, Palette::Yellow);
    ok(U"OK").draw(okPos, Palette::Black);
    no(U"NO").draw(noPos, Palette::Black);

    if (choice[0].leftClicked()) {
      dispChoice = false;
      return true;
    } else if (choice[1].leftClicked()) {
      dispChoice = false;
    }
  }
  return false;
}

void FinishButton::moveAge() {
  moveNum++;
}

}
