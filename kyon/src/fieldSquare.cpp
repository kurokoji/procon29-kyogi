#include "fieldSquare.hpp"

FieldSquare::FieldSquare() : choiceWhiteSquare(0, 0, 30, 30), choiceRedSquare(0, 0, 30, 30), choiceBlueSquare(0, 0, 30, 30), agentMarker(10, 10, 10), isSquareDisp(false), canCancel(false) {}

//座標設定
FieldSquare& FieldSquare::setPos(uint32 x, uint32 y) {
  pos = Vec2(x, y);
  rect.setPos(x, y);
  agentMarker.setPos(x + 50, y + 50);
  choiceWhiteSquare.setPos(x + 60, y);
  choiceRedSquare.setPos(x + 60, y);
  choiceBlueSquare.setPos(x + 60, y);

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

//青チームの選択肢を表示
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

//白を選択した場合
void FieldSquare::choiceWhite() {
  choiceWhiteSquare.draw(Palette::White).drawFrame(0, 3, Palette::Yellow);
  if (choiceWhiteSquare.leftClicked()) {
    clickNum = 0;
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

//clickNumに合わせてマスの色を描画
void FieldSquare::normalSquare() {
  if (clickNum == 0) {
    rect.draw(Palette::White);
  } else if (clickNum == 1) {
    rect.draw(Palette::Red);
  } else if (clickNum == 2) {
    rect.draw(Palette::Blue);
  }
}
