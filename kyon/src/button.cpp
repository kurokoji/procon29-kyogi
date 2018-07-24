#include "button.hpp"
#include <Siv3D.hpp>

int Button::click() {
  if (rect.leftClicked()) {
    clickNum++;
  }

  if (clickNum == 3) {
    clickNum = 0;
  }

  return clickNum;
}
