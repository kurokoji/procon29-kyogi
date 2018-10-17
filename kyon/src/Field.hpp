#ifndef PROCON29_KYON_FIELD_HPP_
#define PROCON29_KYON_FIELD_HPP_


#include <Siv3D.hpp>
#include "FieldSquare.hpp"
#include "ProblemState.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <array>

namespace kyon {

class Field {
private:
  int32 H, W, squSize;
  std::array<int32, 9> dy = {0, 0, -1, -1, -1, 0, 1, 1, 1};
  std::array<int32, 9> dx = {0, -1, -1, 0, 1, 1, 1, 0, -1};
  std::array<std::pair<size_t, size_t>, 2> bluePos, redPos;
  Array<Array<int32>> fieldPoints;
  std::vector<std::vector<FieldSquare>> squares;
  ProblemState problemState;
public:
    Field();
    String convStr(int32);
    bool isInside(const int32, const int32);
    void InitData(int32, int32, Array<Array<int32>>, std::array<std::pair<size_t, size_t>, 2>, std::array<std::pair<size_t, size_t>, 2>);
    void InitField();
    void updateField(int32, int32);
    void drawField();
};

}

#endif
