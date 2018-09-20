#include "fieldSquare.hpp"

FieldSquare::FieldSquare() : choiceWhiteSquare(0, 0, 30, 30), choiceRedSquare(0, 0, 30, 30), choiceBlueSquare(0, 0, 30, 30), isSquareDisp(false), canCancel(false) {}

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

void FieldSquare::update(bool& canMove) {
  if (canMove) {
    if (rect.leftClicked()) {
      isSquareDisp = true;
    } else if (isSquareDisp) {
      canCancel = true;
      choiceColor(canMove, isSquareDisp);
    }
    if (canCancel && rect.leftClicked()) {
      canCancel = false;
      isSquareDisp = false;
    }
  }
}

void FieldSquare::choiceColor(bool& canMove, bool & isSquareDisp) {
  choiceWhiteSquare.draw(Palette::White).drawFrame(0, 3, Palette::Yellow);
  choiceRedSquare.draw(Palette::Red).drawFrame(0, 3, Palette::Yellow);
  choiceBlueSquare.draw(Palette::Blue).drawFrame(0, 3, Palette::Yellow);

  if (choiceWhiteSquare.leftClicked()) {
    clickNum = 0;
    canMove = false;
    isSquareDisp = false;
  } else if (choiceRedSquare.leftClicked()) {
    clickNum = 1;
    canMove = false;
    isSquareDisp = false;
  } else if (choiceBlueSquare.leftClicked()) {
    clickNum = 2;
    canMove = false;
    isSquareDisp = false;
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
