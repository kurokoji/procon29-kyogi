#include "Field.hpp"
#include <Siv3D.hpp>

namespace kyon {
extern bool fieldRev;
Field::Field() : squSize(60) {}

void Field::InitData(ProblemState pState) {
  H = pState.h;
  W = pState.w;
  fieldPoints = pState.field;
  fColor = pState.fieldColor;
  bluePos = pState.blue;
  redPos = pState.red;
  clicked = false;
  b1DispArrow = true;
  b2DispArrow = true;
}

String Field::convStr(int32 num) {
  String str = Format(num);

  return str;
}

void Field::InitField() {
  // squareのサイズをH*Wに初期化*
  squares = Array<Array<FieldSquare>>(H, Array<FieldSquare>(W));

  //全fieldSquareに得点を渡す*
  for (int y : step(H)) {
    for (int x : step(W)) {
      //文字列を数値へ変換
      String str;
      str = convStr(fieldPoints[y][x]);

      squares[y][x].squareNum = str;
    }
  }
  //マスの色を初期化*
  for (int y : step(H)) {
    for (int x : step(W)) {
      if (fColor[y][x] == 1) {
        squares[y][x].whatColor = Color::Blue;
      } else if (fColor[y][x] == 2) {
        squares[y][x].whatColor = Color::Red;
      }
    }
  }
  // Agentがいる位置をonAgentへ渡す*
  for (auto [i, j] : Indexed(bluePos)) {
    squares[j.first][j.second].onAgent = i + 1;
  }

  for (auto [i, j] : Indexed(redPos)) {
    squares[j.first][j.second].onAgent = i + 3;
  }

  prev = squares;
}

bool Field::isInside(const int32 y, const int32 x) {
  return (0 <= y && y < H) && (0 <= x && x < W) && (squares[y][x].onAgent == 0);
}
// AgentがいるSquareの周囲のsquareをupdateする
bool Field::updateField(const int32 y, const int32 x) {
  // agentの値で色の判定*
  String whichColor;
  auto c = squares[y][x].onAgent;

  squares[y][x].rect.drawFrame(2.0, 2.0, Palette::Yellow);
  switch (c) {
  case 1:
    whichColor = U"b1";
    for (int i = 1; i < 9; ++i) {
      if (isInside(y + dy[i], x + dx[i])) {
        int cmp = squares[y + dy[i]][x + dx[i]].update(whichColor);
        if (cmp) {
          if (cmp == 2) {
            squares[y][x].onAgent = 0;
          }
          b1DispArrow = false;
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
        if (cmp) {
          if (cmp == 2) {
            squares[y][x].onAgent = 0;
          }
          b2DispArrow = false;
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
        if (cmp) {
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
        if (cmp) {
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

void Field::updateAgentPos() {
  // Agent位置の更新
  for (int y : step(H)) {
    for (int x : step(W)) {
      if (squares[y][x].onAgent == 1) {
        bluePos[0].first = y;
        bluePos[0].second = x;
      } else if (squares[y][x].onAgent == 2) {
        bluePos[1].first = y;
        bluePos[1].second = x;
      } else if (squares[y][x].onAgent == 3) {
        redPos[0].first = y;
        redPos[0].second = x;
      } else if (squares[y][x].onAgent == 4) {
        redPos[1].first = y;
        redPos[1].second = x;
      }
    }
  }

  //フィールド全体の色を更新
  for (int y : step(H)) {
    for (int x : step(W)) {
      fColor[y][x] = static_cast<int>(squares[y][x].whatColor);
    }
  }
}

// H * W　マスの描画*
void Field::drawField(Array<int> blue) {
  if (fieldRev) {
    for (int x = W - 1; x >= 0; --x) {
      for (int y : step(H)) {

        squares[y][x].setPos(10 + y * squSize, 10 + (W - 1 - x) * squSize);
        squares[y][x].draw();
        squares[y][x].rect.drawFrame(1.0, 1.0, Palette::Gray);

        //矢印の描画
        if (b1DispArrow) {
          bool canMove[8];
          for (int i = 0; i < 9; ++i) {
            canMove[i] = false;
          }

          if (squares[y][x].onAgent == 1) {
            for (int i = 1; i < 9; ++i) {
              if (isInside(y + dy[i], x + dx[i])) {
                canMove[i - 1] = true;
              }
            }
            squares[y][x].dispArrow(blue[0], canMove);
          }
        }

        if (b2DispArrow) {
          bool canMove[8];
          for (int i = 0; i < 9; ++i) {
            canMove[i] = false;
          }
          if (squares[y][x].onAgent == 2) {
            for (int i = 1; i < 9; ++i) {
              if (isInside(y + dy[i], x + dx[i])) {
                canMove[i - 1] = true;
              }
            }
            squares[y][x].dispArrow(blue[1], canMove);
          }
        }

        if (squares[y][x].isClick() && squares[y][x].onAgent != 0) {
          clicked = true;
          agent_x = x;
          agent_y = y;
        }
      }
    }

  } else {
    for (int y = H - 1; y >= 0; --y) {
      for (int x : step(W)) {

        squares[y][x].setPos(10 + (H - 1 - y) * squSize, 10 + x * squSize);
        squares[y][x].draw();
        squares[y][x].rect.drawFrame(1.0, 1.0, Palette::Gray);

        //矢印の描画
        if (b1DispArrow) {
          bool canMove[8];
          for (int i = 0; i < 9; ++i) {
            canMove[i] = false;
          }

          if (squares[y][x].onAgent == 1) {
            for (int i = 1; i < 9; ++i) {
              if (isInside(y + dy[i], x + dx[i])) {
                canMove[i - 1] = true;
              }
            }
            squares[y][x].dispArrow(blue[0], canMove);
          }
        }

        if (b2DispArrow) {
          bool canMove[8];
          for (int i = 0; i < 9; ++i) {
            canMove[i] = false;
          }
          if (squares[y][x].onAgent == 2) {
            for (int i = 1; i < 9; ++i) {
              if (isInside(y + dy[i], x + dx[i])) {
                canMove[i - 1] = true;
              }
            }
            squares[y][x].dispArrow(blue[1], canMove);
          }
        }

        if (squares[y][x].isClick() && squares[y][x].onAgent != 0) {
          clicked = true;
          agent_x = x;
          agent_y = y;
        }
      }
    }

  }
  for (int y : step(H)) {
    for (int x : step(W)) {
      if (clicked && (x == agent_x && y == agent_y)) {
        if (updateField(y, x)) {
          clicked = false;
        }
        /*
           else if (squares[y][x].isClick()){
           clicked = false;
           }*/
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

std::pair<int32, int32> Field::countPoint() {
  int32 blue = 0, red = 0;

  for (int32 i : step(H)) {
    for (int32 j : step(W)) {
      const int32 c = fColor[i][j];
      const int32 score = fieldPoints[i][j];
      if (c == 1) {
        blue += score;
      } else if (c == 2) {
        red += score;
      }
    }
  }

  auto countAreaPoint = [&](int32 c) {
    const int32 dy[] = {0, 1, 0, -1};
    const int32 dx[] = {1, 0, -1, 0};
    Array<Array<bool>> visited(H, Array<bool>(W));
    int32 ret = 0;

    for (int32 i : step(H)) {
      for (int32 j : step(W)) {
        if (visited[i][j])
          continue;
        if (c == 1 && fColor[i][j] == 1)
          continue;
        if (c == 2 && fColor[i][j] == 2)
          continue;

        std::stack<std::pair<int32, int32>> stc;
        stc.emplace(i, j);
        visited[i][j] = true;

        int32 sum = 0;
        bool outSide = false;
        while (!stc.empty()) {
          const int32 y = stc.top().first;
          const int32 x = stc.top().second;
          stc.pop();
          for (int32 k : step(4)) {
            const int32 ny = y + dy[k];
            const int32 nx = x + dx[k];
            if (!(0 <= ny && ny < H && 0 <= nx && nx < W)) {
              outSide = true;
              continue;
            }

            if (visited[ny][nx])
              continue;
            if (c == 1 && fColor[ny][nx] == 1)
              continue;
            if (c == 2 && fColor[ny][nx] == 2)
              continue;

            visited[ny][nx] = true;
            stc.emplace(ny, nx);
          }
          sum += std::abs(fieldPoints[y][x]);
        }
        if (!outSide)
          ret += sum;
      }
    }
    return ret;
  };

  blue += countAreaPoint(1);
  red += countAreaPoint(2);

  return std::make_pair(blue, red);
}
} // namespace kyon
