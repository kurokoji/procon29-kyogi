#include "button.hpp"

class FieldSquare : public Button {
public:
  Rect choiceWhiteSquare;
  Rect choiceRedSquare;
  Rect choiceBlueSquare;
  bool isSquareDisp;

  FieldSquare();
  FieldSquare& setPos(uint32 x, uint32 y);
  FieldSquare& draw(const String& str, bool& hasAgent);
  void normalSquare();
  void update(bool& hasAgent);
};
