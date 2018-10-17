#include "Field.hpp"
#include "FieldSquare.cpp"
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
  //squares = Array<Array<FieldSquare>>(H, Array<FieldSquare>(W));
  squares.resize()
  //全fieldSquareに得点を渡す*
  for (int i : step(H)){
    for (int j : step(W)){
      //文字列を数値へ変換
      String str;
      str = convStr(fieldPoints[i][j]);

      squares[i][j].squareNum = str;
    }
  }
  //Agentがいる位置をonAgentへ渡す*
  for (auto [i, j]: Indexed(bluePos)){
    squares[j.second][j.first].onAgent = i + 1;
  }

  for (auto [i, j]: Indexed(redPos)){
    squares[j.second][j.first].onAgent = i + 3;
  }
}

bool isInside(const int32 x, const int32 y) {
  return (0 <= x &&  x <= W - 1) && (0 <= y && y <= H - 1);
}
//AgentがいるSquareの周囲のsquareをupdateする
void Field::updateField(int32 x, int32 y){
  //agentの値で色の判定*
  String AgentColor;
  if (squares[x][y].onAgent == 1) {
    AgentColor = U"Blue";
    for (int i = 1; i < 9; ++i){
      if (!isInside(x + dx[i], y + dy[i])){
        continue;
      }
      squares[x + dx[i]][y + dy[i]].update(AgentColor);
    }
  }
  else if (squares[x][y].onAgent == 2) {
    AgentColor = U"Blue";
    for (int i = 1; i < 9; ++i){
      if (!isInside(x + dx[i], y + dy[i])){
        continue;
      }
      squares[x + dx[i]][y + dy[i]].update(AgentColor);
    }

  }
  else if(squares[x][y].onAgent == 3){
    AgentColor = U"Red";
    for (int i = 1; i < 9; ++i){
      if (!isInside(x + dx[i], y + dy[i])){
        continue;
      }
      squares[x + dx[i]][y + dy[i]].update(AgentColor);
    }
  }
  else if (squares[x][y].onAgent == 4) {
    AgentColor = U"Red";
    for (int i = 1; i < 9; ++i){
      if (!isInside(x + dx[i], y + dy[i])){
        continue;
      }
      squares[x + dx[i]][y + dy[i]].update(AgentColor);
    }
  }
}

//H * W　マスの描画*
void Field::drawField() {
  for (int i : step(H)) {
    for (int j : step(W)) {
      squares[i][j].setPos(10 + j * squSize, 10 + i * squSize);
      squares[i][j].rect.drawFrame(1.0, 1.0, Palette::Gray);

      //Agentがいたらupdateをかける
      if (squares[i][j].onAgent != 0) {
        updateField(i, j);
      }
    }
  }
}
}
