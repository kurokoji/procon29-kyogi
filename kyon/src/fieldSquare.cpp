#include "fieldSquare.hpp"

FieldSquare::FieldSquare() {
  choiceWhiteSquare = Rect(0, 0, 30, 30);
  choiceRedSquare = Rect(0, 0, 30, 30);
  choiceBlueSquare = Rect(0, 0, 30, 30);
  agentMarker = Circle(10, 10, 10);
  isSquareDisp = false;
  canCancel = false;
  whatColor = 0;
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
  choiceWhiteSquare.setPos(x + 60, y);
  choiceRedSquare.setPos(x + 60, y);
  choiceBlueSquare.setPos(x + 60, y);

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

//赤チームの選択肢を表示
void FieldSquare::choiceRedTeam() {
  if (rect.leftClicked()) {
    isSquareDisp = true;
  } else if (isSquareDisp) {
    canCancel = true;
    if(whatColor == 0) {
      choiceRedSquare.draw(Palette::Red).drawFrame(0, 3, Palette::Yellow);
      if (choiceRedSquare.leftClicked()) {
        whatColor = 1;
        isSquareDisp = false;
      }
    } else if (whatColor == 2) {
      choiceWhite();
    }
  }
}

//青チームの選択肢を表示
void FieldSquare::choiceBlueTeam() {
  if (rect.leftClicked()) {
    isSquareDisp = true;
  } else if (isSquareDisp) {
    canCancel = true;
    if(whatColor == 0) {
      choiceBlueSquare.draw(Palette::Blue).drawFrame(0, 3, Palette::Yellow);
      if (choiceBlueSquare.leftClicked()) {
        whatColor = 2;
        isSquareDisp = false;
      }
    } else if (whatColor == 1) {
      choiceWhite();
    }
  }
}

//白を選択した場合
void FieldSquare::choiceWhite() {
  choiceWhiteSquare.draw(Palette::White).drawFrame(0, 3, Palette::Yellow);
  if (choiceWhiteSquare.leftClicked()) {
    whatColor = 0;
    isSquareDisp = false;
  }
}

//選択肢の非表示
void FieldSquare::dispCancel() {
  if (canCancel && rect.leftClicked()) {
    canCancel = false;
    isSquareDisp = false;
  }
}

//whatColorに合わせてマスの色を描画 (0は白,1は赤,2は青です)
void FieldSquare::normalSquare() {
  if (whatColor == 0) {
    rect.draw(Palette::White);
  } else if (whatColor == 1) {
    rect.draw(Palette::Red);
  } else if (whatColor == 2) {
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
