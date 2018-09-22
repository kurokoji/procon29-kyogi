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
  void choiceRedTeam();
  void choiceBlueTeam();
  void choiceWhite();
  void dispCancel();
  void normalSquare();
  void update(const String& whichAgent);
  void update(const String&& whichAgent);
};
