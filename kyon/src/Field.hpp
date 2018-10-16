#ifndef PROCON29_KYON_FIELD_HPP_
#define PROCON29_KYON_FIELD_HPP_

#include <Siv3D.hpp>
#include "fieldSquare.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <array>

class Field {
private:
    int32 H, W, squSize;
    std::array<int32, 9> dy = {0, 0, -1, -1, -1, 0, 1, 1, 1};
    std::array<int32, 9> dx = {0, -1, -1, 0, 1, 1, 1, 0, -1};
    std::array<std::pair<size_t, size_t>, 2> bluePos, redPos;
    String ColorAgent;

    Array<Array<int32>> fieldPoints;
    Array<Array<FieldSquare>> squares;
public:
    Field();
    String convStr(int32);
    bool isInside(const int32, const int32);
    void InitData(const std::tuple<int32, int32, Array<Array<int32>>, std::array<std::pair<size_t, size_t>>>);
    void InitField();
    void updateField(int32, int32);
    void drawField();
};

#endif
