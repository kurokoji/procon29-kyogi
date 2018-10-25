#include "Field.hpp"
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
    clicked = false;
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

        squares[y][x].squareNum = str;
      }
    }
    //マスの色を初期化*
    for (int y : step(H)){
      for (int x : step(W)){
        if (fColor[y][x] == 1){
          squares[y][x].whatColor = Color::Blue;
        }
        else if(fColor[y][x] == 2){
          squares[y][x].whatColor = Color::Red;
        }
      }
    }
    //Agentがいる位置をonAgentへ渡す*
    for (auto [i, j]: Indexed(bluePos)){
      squares[j.first][j.second].onAgent = i + 1;
    }

    for (auto [i, j]: Indexed(redPos)){
      squares[j.first][j.second].onAgent = i + 3;
    }
  }

  bool Field::isInside(const int32 y, const int32 x) {
    return (0 <= y &&  y < H) && (0 <= x && x < W) &&
            (squares[y][x].onAgent == 0);
  }
  //AgentがいるSquareの周囲のsquareをupdateする
  bool Field::updateField(const int32 y, const int32 x){
    //agentの値で色の判定*
    String whichColor;
    auto c = squares[y][x].onAgent;

    squares[y][x].rect.drawFrame(2.0, 2.0, Palette::Yellow);
    switch (c) {
      case 1:
        whichColor = U"b1";
        for (int i = 1; i < 9; ++i) {
          if (isInside(y + dy[i], x + dx[i])) {
            int cmp = squares[y + dy[i]][x + dx[i]].update(whichColor);
            if (cmp){
              if (cmp == 2) {
                squares[y][x].onAgent = 0;
              }
              return true;
            }
          }
        }
        break;
      case 2:
        whichColor = U"b2";
        for (int i = 1; i < 9; ++i) {
          if (isInside(y + dy[i], x + dx[i])) {
            int cmp = squares[y + dy[i]][x + dx[i]].update(whichColor);
            if (cmp){
              if (cmp == 2) {
                squares[y][x].onAgent = 0;
              }
              return true;
            }
          }
        }
        break;
      case 3:
        whichColor = U"r1";
        for (int i = 1; i < 9; ++i) {
          if (isInside(y + dy[i], x + dx[i])) {
            int cmp = squares[y + dy[i]][x + dx[i]].update(whichColor);
            if (cmp){
              if (cmp == 2) {
                squares[y][x].onAgent = 0;
              }
              return true;
            }
          }
        }
        break;
      case 4:
        whichColor = U"r2";
        for (int i = 1; i < 9; ++i) {
          if (isInside(y + dy[i], x + dx[i])) {
            int cmp = squares[y + dy[i]][x + dx[i]].update(whichColor);
            if (cmp){
              if (cmp == 2) {
                squares[y][x].onAgent = 0;
              }
              return true;
            }
          }
        }
        break;
    }
    return false;
  }
    
  void Field::updateAgentPos(){
      //Agent位置の更新
      for (int y : step(H)){
        for (int x : step(W)){
          if (squares[y][x].onAgent == 1){
            bluePos[0].first = y;
            bluePos[0].second = x;
          }
          else if (squares[y][x].onAgent == 2){
            bluePos[1].first = y;
            bluePos[1].second = x;
          }
          else if (squares[y][x].onAgent == 3){
            redPos[0].first = y;
            redPos[0].second = x;
          }
          else if (squares[y][x].onAgent == 4){
            redPos[1].first = y;
            redPos[1].second = x;
          }
        }
      }

      //フィールド全体の色を更新
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
          squares[y][x].draw();
          squares[y][x].rect.drawFrame(1.0, 1.0, Palette::Gray);

          if (squares[y][x].isClick() && squares[y][x].onAgent != 0) {
            clicked = true;
            agent_x = x;
            agent_y = y;
          }
        }
      }
      for (int y : step(H)){
        for (int x : step(W)){
          if (clicked && (x == agent_x && y == agent_y)){
            if (updateField(y, x)) {
              clicked = false;
            }
          }
        }
      }
      updateAgentPos();
    }
  }
}

std::string Field::to_string() {
  auto itos = [](int32 n) { return Format(n).narrow(); };

  std::string ret = "";
  ret += itos(H) + " " + itos(W) + "\n";

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      ret += (j != 0 ? " " : "");
      ret += itos(fieldPoints[i][j]);
    }
    ret += "\n";
  }

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      ret += (j != 0 ? " " : "");
      ret += itos(fColor[i][j]);
    }
    ret += "\n";
  }

  for (auto e : bluePos) {
    ret += itos(e.first) + " " + itos(e.second) + "\n";
  }

  for (auto e : redPos) {
    ret += itos(e.first) + " " + itos(e.second) + "\n";
  }

  return ret;
}
}
