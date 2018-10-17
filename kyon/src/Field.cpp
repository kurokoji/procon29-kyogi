#include "Field.hpp"
#include <Siv3D.hpp>

Field::Field() : squSize(60) {}

void Field::InitData(int32 h, int32 w, Array<Array<int32>> fieldData, std::array<std::pair<size_t, size_t>> bPos, std::array<std::pair<size_t, size_t>> rPos) {
  H = h;
  W = w;
  fieldPoints = fieldData;
  bluePos = bPos;
  redPos = rPos;
}

String Field::convStr(int32 num) {
  String str = Format(num);

  return str;
}

void Field::InitField(){
  //squareのサイズをH*Wに初期化*
  squares = Array<Array<FieldSquare>>(H, Array<FieldSquare>(W));

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
  for (auto [i, j]: Indexed(positions)){
    squares[j.second][j.first].onAgent = i + 1;
  }
}

bool isInside(const int32 x, const int32 y) {
  return (0 <= x &&  x <= W - 1) && (0 <= y && y <= H - 1);
}
//AgentがいるSquareの周囲のsquareをupdateする
void Field::updateField(int32 x, int32 y){
  //agentの値で色の判定*
  String AgentColor;
  if (squares[i][j].agent == 1) {
    AgentColor = U"Blue";
    for (int i = 1; i < 9; ++i){
      if (!inInside(i + dx[i], j + dy[i])){
        continue;
      }
      squares[i + dx[i]][j + dy[i]].update(AgentColor);
    }
  }
  else if (squares[i][j].agent == 2) {
    AgentColor = U"Blue";
    for (int i = 1; i < 9; ++i){
      if (!inInside(i + dx[i], j + dy[i])){
        continue;
      }
      squares[i + dx[i]][j + dy[i]].update(AgentColor);
    }

  }
  else if(squares[i][j].agent == 3){
    AgentColor = U"Red";
    for (int i = 1; i < 9; ++i){
      if (!inInside(i + dx[i], j + dy[i])){
        continue;
      }
      squares[i + dx[i]][j + dy[i]].update(AgentColor);
    }
  }
  else if (squares[i][j].agent == 4) {
    AgentColor = U"Red";
    for (int i = 1; i < 9; ++i){
      if (!inInside(i + dx[i], j + dy[i])){
        continue;
      }
      squares[i + dx[i]][j + dy[i]].update(AgentColor);
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
