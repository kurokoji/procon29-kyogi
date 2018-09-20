#include "button.hpp"

class FieldSquare : public Button {
public:
  Rect choiceWhiteSquare;
  Rect choiceRedSquare;
  Rect choiceBlueSquare;
  bool isSquareDisp;
  bool canCancel;

  FieldSquare();
  FieldSquare& setPos(uint32 x, uint32 y);
  FieldSquare& draw(const String& str, bool& hasAgent);
  void normalSquare();
  void choiceColor(bool &canMove, bool& isSquareDisp);
  void update(bool& canMove);
};
