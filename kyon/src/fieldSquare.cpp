#include "fieldSquare.hpp"


namespace kyon {
FieldSquare::FieldSquare() {
  for (int i = 0; i < 4; ++i) {
    choiceColor[i] = Rect(0, 0, 30, 30);
  }
  agentMarker = Circle(10, 10, 10);
  isSquareDisp = false;
  canCancel = false;
  whatColor = Color::None;
  solverArrowPath = U"../../../image/ArrowImage/Yellow.png";
  normalArrowPath = U"../../../image/ArrowImage/Gray.png";
  solverArrow = Texture(solverArrowPath);
  normalArrow = Texture(normalArrowPath);
}

//座標設定
FieldSquare& FieldSquare::setPos(uint32 x, uint32 y) {
  pos = Vec2(x, y);
  rect.setPos(x, y);
  agentMarker.setPos(x + 50, y + 50);

  for (int i = 0; i < 2; ++i) {
    choiceColor[i] = Rect(0, 0, 30, 30);
  }

  choiceColor[0].setPos(x + 60, y);
  choiceColor[1].setPos(x + 60, y + 40);

  arrowX[0] = x;
  arrowY[0] = y + 25;
  arrowX[1] = x;
  arrowY[1] = y;
  arrowX[2] = x + 25;
  arrowY[2] = y;
  arrowX[3] = x + 49;
  arrowY[3] = y;
  arrowX[4] = x + 49;
  arrowY[4] = y + 25;
  arrowX[5] = x + 49;
  arrowY[5] = y + 49;
  arrowX[6] = x + 25;
  arrowY[6] = y + 49;
  arrowX[7] = x;
  arrowY[7] = y + 49;

  return *this;
}

//マスを表示
FieldSquare& FieldSquare::draw(const String& str, bool& hasAgent) {
  if (hasAgent) {
    normalSquare();
    agentMarker.draw(Palette::Purple);
  } else {
    normalSquare();
  }
  font(str).draw(pos, Palette::Black);

  return *this;
}

//マスをクリックしたときの挙動

void FieldSquare::update(const String whichAgent[]) {
  bool dispRedRect = false;
  bool dispBlueRect = false;
  for (auto& i : step(2)) {
    if (whichAgent[i] == U"Red") {
      dispRedRect = true;
    } else if (whichAgent[i] == U"Blue") {
      dispBlueRect = true;
    }
  }

  if (rect.leftClicked()) {
    isSquareDisp = true;
  } else if (isSquareDisp) {
    canCancel = true;
    if (dispRedRect) {
      if (whatColor == Color::None) {
        choiceColor[0].draw(Palette::Red);
        if (choiceColor[0].leftClicked()) {
          whatColor = Color::Red;
          isSquareDisp = false;
        }
      } else if (whatColor == Color::Red) {
        choiceColor[0].draw(Palette::Red);
        if (choiceColor[0].leftClicked()) {
          isSquareDisp = false;
        }
      } else if (whatColor == Color::Blue) {
        choiceColor[0].draw(Palette::White);
        if (choiceColor[0].leftClicked()) {
          whatColor = Color::None;
          isSquareDisp = false;
        }
      }
    }
    if (dispBlueRect) {
      if(whatColor == Color::None) {
        choiceColor[1].draw(Palette::Blue);
        if (choiceColor[1].leftClicked()) {
          whatColor = Color::Blue;
          isSquareDisp = false;
        }
      } else if (whatColor == Color::Red) {
        choiceColor[1].draw(Palette::White);
        if (choiceColor[1].leftClicked()) {
          whatColor = Color::None;
          isSquareDisp = false;
        }
      } else if (whatColor == Color::Blue) {
        choiceColor[1].draw(Palette::Blue);
        if (choiceColor[1].leftClicked()) {
          isSquareDisp = false;
        }
      }
    }
  }
  dispCancel();
}

//選択肢の非表示
void FieldSquare::dispCancel() {
  if (canCancel && rect.leftClicked()) {
    canCancel = false;
    isSquareDisp = false;
  }
}

//whatColorに合わせてマスの色を描画
void FieldSquare::normalSquare() {
  if (whatColor == Color::None) {
    rect.draw(Palette::White);
  } else if (whatColor == Color::Red) {
    rect.draw(Palette::Red);
  } else if (whatColor == Color::Blue) {
    rect.draw(Palette::Blue);
  }
}

void FieldSquare::dispArrow(int32 solverDirection, bool canMove[]) {
  int32 arrowRadians = 0;
  for (auto i : step(8)) {
    if (canMove[i] && i != solverDirection - 1) {
      normalArrow.scaled(0.02).rotated(Radians(arrowRadians)).draw(arrowX[i], arrowY[i]);
      arrowRadians += 45;
    } else if (canMove[i] && i == solverDirection - 1) {
      solverArrow.scaled(0.02).rotated(Radians(arrowRadians)).draw(arrowX[i], arrowY[i]);
      arrowRadians += 45;
    } else {
      arrowRadians += 45;
    }
  }
}
}
