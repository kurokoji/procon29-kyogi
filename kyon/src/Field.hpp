#ifndef PROCON29_KYON_FIELD_HPP_
#define PROCON29_KYON_FIELD_HPP_

#include "FieldSquare.hpp"
#include "ProblemState.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <Siv3D.hpp>

namespace kyon {

class Field {
private:
    int32 H, W;
    int32 squSize;
    Image image;
    DynamicTexture texture;
    std::vector<std::vector<FieldSquare>> squares;
    ProblemState problemState;
public:
    Field();
    Field(int32 h, int32 w);

    void InitField();
    void updateField();
    void drawField(const String& str, bool& hasAgent);
};

}

#endif
