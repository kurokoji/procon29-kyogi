#ifndef PROCON29_KYON_BUTTON_HPP_
#define PROCON29_KYON_BUTTON_HPP_

#include <Siv3D.hpp>

struct Button : public Rect {
  int clickNum = 0;
  Rect rect = Rect(0, 0, 60, 60);
  int click();
};

#endif
