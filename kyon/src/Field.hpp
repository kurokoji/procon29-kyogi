#ifndef PROCON29_KYON_FIELD_HPP_
#define PROCON29_KYON_FIELD_HPP_


#include <Siv3D.hpp>
#include "FieldSquare.hpp"
#include "ProblemState.hpp"
#include "Color.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <array>

namespace kyon {

class Field {
private:
  int32 H, W, squSize;
  int32 agent_x, agent_y;
  bool clicked;
  std::array<int32, 9> dy = {0, 0, -1, -1, -1, 0, 1, 1, 1};
  std::array<int32, 9> dx = {0, -1, -1, 0, 1, 1, 1, 0, -1};
  std::array<std::pair<size_t, size_t>, 2> bluePos, redPos;
  Array<Array<int32>> fieldPoints;
  Array<Array<int32>> fColor;
  Array<Array<FieldSquare>> squares;
public:
    Field();
    void InitData(ProblemState);
    String convStr(int32);
    void InitField();
    bool isInside(const int32, const int32);
    bool updateField(const int32, const int32);
    void updateAgentPos();
    void drawField();
};

}

#endif
