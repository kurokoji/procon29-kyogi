#include "Field.hpp"
#include "FieldSquare.hpp"
#include <Siv3D.hpp>

namespace kyon {
Field::Field() : squSize(60) {}

void Field::InitData(ProblemState pState) {
  H = pState.h;
  W = pState.w;
  fieldPoints = pState.field;
  fColor = pState.fieldColor;
  bluePos = pState.blue;
  redPos = pState.red;
}

String Field::convStr(int32 num) {
  String str = Format(num);

  return str;
}

void Field::InitField(){
  //squareのサイズをH*Wに初期化*
  squares = Array<Array<FieldSquare>>(H, Array<FieldSquare>(W));

  //全fieldSquareに得点を渡す*
  for (int y : step(H)){
    for (int x : step(W)){
      //文字列を数値へ変換
      String str;
      str = convStr(fieldPoints[y][x]);

      squares[i][j].squareNum = str;
    }
  }
  //Agentがいる位置をonAgentへ渡す*
  for (auto [i, j]: Indexed(redPos)){
    squares[j.first][j.second].onAgent = i + 1;
  }

  for (auto [i, j]: Indexed(bluePos)){
    squares[j.first][j.second].onAgent = i + 3;
  }
}

bool Field::isInside(const int32 y, const int32 x) {
  return (0 <= x &&  x <= W - 1) && (0 <= y && y <= H - 1);
}
//AgentがいるSquareの周囲のsquareをupdateする
void Field::updateField(const int32 y, const int32 x){
  //agentの値で色の判定*
  String whichColor;
  auto c = squares[y][x].onAgent;
  switch (c) {
    case 1:
      whichColor = U"r1";
      for (int i = 1; i < 9; ++i) {
        if (!isInside(y + dy[i], x + dx[i])) {
          continue;
        }
        if (squares[y + dy[i]][x + dx[i]].update(AgentColor)){
          squares[y][x].onAgent = 0;
        }
      }
      break;
    case 2:
      whichColor = U"r2";
      for (int i = 1; i < 9; ++i) {
        if (!isInside(y + dy[i], x + dx[i])) {
          continue;
        }
        if (squares[y + dy[i]][x + dx[i]].update(AgentColor)){
          squares[y][x].onAgent = 0;
        }
      }
      break;
    case 3:
      whichColor = U"b1";
      for (int i = 1; i < 9; ++i) {
        if (!isInside(y + dy[i], x + dx[i])) {
          continue;
        }
        if (squares[y + dy[i]][x + dx[i]].update(AgentColor)){
          squares[y][x].onAgent = 0;
        }
      }
      break;
    case 4:
      whichColor = U"b2";
      for (int i = 1; i < 9; ++i) {
        if (!isInside(y + dy[i], x + dx[i])) {
          continue;
        }
        if (squares[y + dy[i]][x + dx[i]].update(AgentColor)){
          squares[y][x].onAgent = 0;
        }
      }
      break;
  }
  //Agent位置の更新
  for (int y : step(H)){
    for (int x : step(W)){
      if (squares[y][x] == 1){
       redPos[0].first = H;
       redPos[0].second = W;
      }
      else if (squares[y][x] == 2){
        redPos[1].first = H;
        redPos[1].second = W;
      }
      else if (squares[y][x] == 3){
        bluePos[0].first = H;
        bluePos[0].second = W;
      }
      else if (squares[y][x] == 4){
        bluePos[1].first = H;
        bluePos[1].second = W;
      }
    }
  }

  for (int y : step(H)){
    for (int x : step(W)){
      fColor[y][x] = static_cast<int>(squares[y][x].whatColor);
    }
  }
}

//H * W　マスの描画*
void Field::drawField() {
  for (int y : step(H)) {
    for (int x : step(W)) {
      squares[y][x].setPos(10 + x * squSize, 10 + y * squSize);
      squares[y][x].rect.drawFrame(1.0, 1.0, Palette::Gray);

      //Agentがいたらupdateをかける
      if (squares[y][x].rect.leftClicked()) {
        updateField(y, x);
      }
    }
  }
}
}
