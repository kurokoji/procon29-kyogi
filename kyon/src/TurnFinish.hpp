#ifndef PROCON29_KYON_TURN_FINISH_HPP_
#define PROCON29_KYON_TURN_FINISH_HPP_

#include <Siv3D.hpp>

namespace kyon {

class FinishButton {
public:
  Rect finishRect;
  Rect choice[2];
  Font ok;
  Font no;
  int32 moveNum;
  Vec2 okPos;
  Vec2 noPos;
  bool dispChoice;

  FinishButton();
  FinishButton& setPos(int32 x, int32 y);
  bool draw();
  void moveAge();
};

}

#endif
