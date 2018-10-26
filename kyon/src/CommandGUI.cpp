#include "CommandGUI.hpp"
#include <Siv3D.hpp>

namespace kyon {
CommandGUI::CommandGUI() {}

CommandGUI::CommandGUI(int32 recX, int32 recY){
  x = recX;
  y = recY;
}

void CommandGUI::selectImg(int32 b1, int32 b2){
  switch(b1){
    case 0:
      nemu = U"../../../image/HandL00.png";
      break;
    case 1:
      nemu = U"../../../image/HandL01.png";
      break;
    case 2:
      nemu = U"../../../image/HandL02.png";
      break;
    case 3:
      nemu = U"../../../image/HandL03.png";
      break;
    case 4:
      nemu = U"../../../image/HandL04.png";
      break;
    case 5:
      nemu = U"../../../image/HandL05.png";
      break;
    case 6:
      nemu = U"../../../image/HandL01.png";
      break;
    case 7:
      nemu = U"../../../image/HandL02.png";
      break;
    case 8:
      nemu = U"../../../image/HandL03.png";
      break;
    default:
      break;
  }
  switch (b2){
    case 0:
      higashi = U"../../../image/HandR00.png";
      break;
    case 1:
      higashi = U"../../../image/HandR01.png";
      break;
    case 2:
      higashi = U"../../../image/HandR02.png";
      break;
    case 3:
      higashi = U"../../../image/HandR03.png";
      break;
    case 4:
      higashi = U"../../../image/HandR04.png";
      break;
    case 5:
      higashi = U"../../../image/HandR05.png";
      break;
    case 6:
      higashi = U"../../../image/HandR01.png";
      break;
    case 7:
      higashi = U"../../../image/HandR02.png";
      break;
    case 8:
      higashi = U"../../../image/HandR03.png";
      break;
    default:
      break;
  }
}

void CommandGUI::dispCmd(int32 b1, int32 b2){
  const Rect rect(x, y, 380, 270);
  const Texture rImg(higashi);
  const Texture lImg(nemu);
  const Circle agent1(x + 40, y + 40, 20);
  const Triangle agent2(x + 200, y + 40, 40);
  const Font Agents(50);
  const Font str40(40);
  String str1, str2;

  str1 = Format(b1);
  str2 = Format(b2);

  selectImg(b1, b2);
  rect.draw(Palette::Skyblue);

  rImg.draw(x + 220, y + 80);
  lImg.draw(x + 40, y + 80);

  agent2.draw(Palette::Blueviolet);
  agent1.draw(Palette::Blueviolet);

  str40(str1).draw(x + 140, y + 30, Palette::Crimson);
  str40(str2).draw(x + 320, y + 30, Palette::Crimson);
  
  if (b1 >= 6){
    str40(U"裏").draw(x + 80, y + 30, Palette::Black);
  }
  if (b2 >= 6){
    str40(U"裏").draw(x + 260, y + 30, Palette::Black);
  }
}
}
