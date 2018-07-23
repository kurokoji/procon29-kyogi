#include "button.hpp"
#include <Siv3D.hpp>

int Button::click() {
  if (rect.leftClicked()) {
    clicknum++;
  }

  if (clicknum == 3) {
    clicknum = 0;
  }

  return clicknum;
}
