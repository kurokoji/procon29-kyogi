#include "button.hpp"

class FieldSquare : public Button {
public:
  FieldSquare& draw(const String& str, bool& hasAgent);
  void normalSquare();
};
