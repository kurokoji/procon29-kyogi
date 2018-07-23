#include "button.hpp"
#include <Siv3D.hpp>

bool Button::canClick() {
  if (rect.mouseOver()) {
    return (true);
  }
  else {
    return (false);
  }
}


int Button::click(/*int &click_num, Rect rect*/) {
  if (canClick()) {
    if (rect.leftClicked()) {
      clicknum++;
    }
  }

  if (clicknum == 3) {
    clicknum = 0;
  }

  return (clicknum);
 }
