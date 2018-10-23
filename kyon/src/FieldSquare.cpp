#include "FieldSquare.hpp"


namespace kyon {
FieldSquare::FieldSquare() {
  onAgent = 0;
  squareNum = U"None";
  choiceColor = Rect(0, 0, 30, 30);
  agent1Marker = Circle(10, 10, 10);
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
  agent1Marker.setPos(x + 50, y + 50);
  agent2Marker = Triangle(x + 50, y + 53, 20, 0_deg);

  choiceColor.setPos(x + 60, y);

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
FieldSquare& FieldSquare::draw() {
  if (onAgent == 0) {
    normalSquare();
  } else {
    normalSquare();
    if (onAgent == 1) {
      agent1Marker.draw(Palette::Purple);
    } else if (onAgent == 2) {
      agent2Marker.draw(Palette::Purple);
    } else if (onAgent == 3) {
      agent1Marker.draw(Palette::Orange);
    } else if (onAgent == 4) {
      agent2Marker.draw(Palette::Orange);
    }
  }
  font(squareNum).draw(pos, Palette::Black);

  return *this;
}

//マスをクリックしたときの挙動

bool FieldSquare::update(const String whichAgent) {
  if (rect.leftClicked()) {
    isSquareDisp = true;
  } else if (isSquareDisp) {
    canCancel = true;
    if (whichAgent == U"r1") {
      if (whatColor == Color::None) {
        choiceColor.draw(Palette::Red);
        if (choiceColor.leftClicked()) {
          whatColor = Color::Red;
          onAgent = 3;
          isSquareDisp = false;
          return 1;
        }
      } else if (whatColor == Color::Red) {
        choiceColor.draw(Palette::Red);
        if (choiceColor.leftClicked()) {
          onAgent = 3;
          isSquareDisp = false;
          return 1;
        }
      } else if (whatColor == Color::Blue) {
        choiceColor.draw(Palette::White);
        if (choiceColor.leftClicked()) {
          whatColor = Color::None;
          isSquareDisp = false;
          return 0;
        }
      }
    } else if (whichAgent == U"r2") {
      if (whatColor == Color::None) {
        choiceColor.draw(Palette::Red);
        if (choiceColor.leftClicked()) {
          whatColor = Color::Red;
          onAgent = 4;
          isSquareDisp = false;
          return 1;
        }
      } else if (whatColor == Color::Red) {
        choiceColor.draw(Palette::Red);
        if (choiceColor.leftClicked()) {
          onAgent = 4;
          isSquareDisp = false;
          return 1;
        }
      } else if (whatColor == Color::Blue) {
        choiceColor.draw(Palette::White);
        if (choiceColor.leftClicked()) {
          whatColor = Color::None;
          isSquareDisp = false;
          return 0;
        }
      }
    } else if (whichAgent == U"b1") {
      if(whatColor == Color::None) {
        choiceColor.draw(Palette::Blue);
        if (choiceColor.leftClicked()) {
          whatColor = Color::Blue;
          onAgent = 1;
          isSquareDisp = false;
          return 1;
        }
      } else if (whatColor == Color::Red) {
        choiceColor.draw(Palette::White);
        if (choiceColor.leftClicked()) {
          whatColor = Color::None;
          isSquareDisp = false;
          return 0;
        }
      } else if (whatColor == Color::Blue) {
        choiceColor.draw(Palette::Blue);
        if (choiceColor.leftClicked()) {
          onAgent = 1;
          isSquareDisp = false;
          return 1;
        }
      }
    } else if (whichAgent == U"b2") {
      if(whatColor == Color::None) {
        choiceColor.draw(Palette::Blue);
        if (choiceColor.leftClicked()) {
          whatColor = Color::Blue;
          onAgent = 2;
          isSquareDisp = false;
          return 1;
        }
      } else if (whatColor == Color::Red) {
        choiceColor.draw(Palette::White);
        if (choiceColor.leftClicked()) {
          whatColor = Color::None;
          isSquareDisp = false;
          return 0;
        }
      } else if (whatColor == Color::Blue) {
        choiceColor.draw(Palette::Blue);
        if (choiceColor.leftClicked()) {
          onAgent = 2;
          isSquareDisp = false;
          return 1;
        }
      }
    }
  }
  dispCancel();
  return 0;
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
