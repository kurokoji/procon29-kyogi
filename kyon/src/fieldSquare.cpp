#include "fieldSquare.hpp"

FieldSquare::FieldSquare() : choiceWhiteSquare(0, 0, 30, 30), choiceRedSquare(0, 0, 30, 30), choiceBlueSquare(0, 0, 30, 30), isSquareDisp(false) {}

FieldSquare& FieldSquare::setPos(uint32 x, uint32 y) {
  pos = Vec2(x, y);
  rect.setPos(x, y);
  choiceWhiteSquare.setPos(x + 60, y);
  choiceRedSquare.setPos(x + 60, y + 60);
  choiceBlueSquare.setPos(x + 60, y + 120);

  return *this;
}

FieldSquare& FieldSquare::draw(const String& str, bool& hasAgent) {
  if (hasAgent) {
    rect.draw(Palette::Green);
    if (rect.leftClicked()) {
      normalSquare();
    }
  } else {
    normalSquare();
  }
  font(str).draw(pos, Palette::Black);

  return *this;
}

void FieldSquare::update(bool& hasAgent) {
  if (hasAgent) {
    if (rect.leftClicked() || isSquareDisp == true) {
      isSquareDisp = true;
      choiceWhiteSquare.draw(Palette::White).drawFrame(0, 5, Palette::Yellow);
      choiceRedSquare.draw(Palette::Red).drawFrame(0, 5, Palette::Yellow);
      choiceBlueSquare.draw(Palette::Blue).drawFrame(0, 5, Palette::Yellow);

      if (choiceWhiteSquare.leftClicked()) {
        clickNum = 0;
        hasAgent = false;
        isSquareDisp = false;
      } else if (choiceRedSquare.leftClicked()) {
        clickNum = 1;
        hasAgent = false;
        isSquareDisp = false;
      } else if (choiceBlueSquare.leftClicked()) {
        clickNum = 2;
        hasAgent = false;
        isSquareDisp = false;
      }
    }
  }
}

void FieldSquare::normalSquare() {
  if (clickNum == 0) {
    rect.draw(Palette::White);
  } else if (clickNum == 1) {
    rect.draw(Palette::Red);
  } else if (clickNum == 2) {
    rect.draw(Palette::Blue);
  }
}
