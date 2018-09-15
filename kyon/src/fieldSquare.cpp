#include "fieldSquare.hpp"

FieldSquare& FieldSquare::draw(const String& str, bool& hasAgent) {
  if (hasAgent) {
    rect.draw(Palette::Green);
    if (rect.leftClicked()) {
      hasAgent = false;
      normalSquare();
    }
  } else {
    normalSquare();
  }
  font(str).draw(pos, Palette::Black);

  return *this;
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
