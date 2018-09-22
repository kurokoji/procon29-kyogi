#include "fieldSquare.hpp"

FieldSquare::FieldSquare() : choiceWhiteSquare(0, 0, 30, 30), choiceRedSquare(0, 0, 30, 30), choiceBlueSquare(0, 0, 30, 30), isSquareDisp(false), canCancel(false) {}

FieldSquare& FieldSquare::setPos(uint32 x, uint32 y) {
  pos = Vec2(x, y);
  rect.setPos(x, y);
  choiceWhiteSquare.setPos(x + 60, y);
  choiceRedSquare.setPos(x + 60, y);
  choiceBlueSquare.setPos(x + 60, y);

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

void FieldSquare::update(const String& whichAgent) {
  if (whichAgent == U"Red") {
    choiceRedTeam();
    dispCancel();
  } else if (whichAgent == U"Blue") {
    choiceBlueTeam();
    dispCancel();
  }
}

void FieldSquare::update(const String&& whichAgent) {
  if (whichAgent == U"Red") {
    choiceRedTeam();
    dispCancel();
  } else if (whichAgent == U"Blue") {
    choiceBlueTeam();
    dispCancel();
  }
}

void FieldSquare::choiceRedTeam() {
  if (rect.leftClicked()) {
    isSquareDisp = true;
  } else if (isSquareDisp) {
    canCancel = true;
    if(clickNum == 0) {
      choiceRedSquare.draw(Palette::Red).drawFrame(0, 3, Palette::Yellow);
      if (choiceRedSquare.leftClicked()) {
        clickNum = 1;
        isSquareDisp = false;
      }
    } else if (clickNum == 2) {
      choiceWhite();
    }
  }
}

void FieldSquare::choiceBlueTeam() {
  if (rect.leftClicked()) {
    isSquareDisp = true;
  } else if (isSquareDisp) {
    canCancel = true;
    if(clickNum == 0) {
      choiceBlueSquare.draw(Palette::Blue).drawFrame(0, 3, Palette::Yellow);
      if (choiceBlueSquare.leftClicked()) {
        clickNum = 2;
        isSquareDisp = false;
      }
    } else if (clickNum == 1) {
      choiceWhite();
    }
  }
}

void FieldSquare::choiceWhite() {
  choiceWhiteSquare.draw(Palette::White).drawFrame(0, 3, Palette::Yellow);
  if (choiceWhiteSquare.leftClicked()) {
    clickNum = 0;
    isSquareDisp = false;
  }
}

void FieldSquare::dispCancel() {
  if (canCancel && rect.leftClicked()) {
    canCancel = false;
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
