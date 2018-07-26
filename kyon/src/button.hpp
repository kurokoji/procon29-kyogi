#ifndef PROCON29_KYON_BUTTON_HPP_
#define PROCON29_KYON_BUTTON_HPP_

#include <Siv3D.hpp>

struct Button : public Rect {
  int32 clickNum = 0;
  Font font = Font(40);
  Rect rect = Rect(0, 0, 60, 60);
  void dispSquareNum(int32 onSquareNum, int32 x, int32 y);
  int32 click();
};

#endif
