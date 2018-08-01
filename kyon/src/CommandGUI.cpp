#include "CommandGUI.hpp"
#include <Siv3D.hpp>

CommandGUI::CommandGUI(int32 recX, int32 recY){
  x = recX;
  y = recY;
}

void CommandGUI::convInt(std::string s){
  ss << s;
  ss >> cmd;
}

void CommandGUI::selectImg(int32 cmd){
  switch(cmd){
    case 0:
      rPath = U"../image/HandR00.png";
      lPath = U"../image/HandL00.png";
      break;
    case 1:
      rPath = U"../image/HandR01.png";
      lPath = U"../image/HandL00.png";
      break;
    case 2:
      rPath = U"../image/HandR02.png";
      lPath = U"../image/HandL00.png";
      break;
    case 3:
      rPath = U"../image/HandR03.png";
      lPath = U"../image/HandL00.png";
      break;
    case 4:
      rPath = U"../image/HandR04.png";
      lPath = U"../image/HandL00.png";
      break;
    case 5:
      rPath = U"../image/HandR05.png";
      lPath = U"../image/HandL00.png";
      break;
    case 6:
      rPath = U"../image/HandR05.png";
      lPath = U"../image/HandL01.png";
      break;
    case 7:
      rPath = U"../image/HandR05.png";
      lPath = U"../image/HandL02.png";
      break;
    case 8:
      rPath = U"../image/HandR05.png";
      lPath = U"../image/HandL03.png";
      break;
    default:
      break;
  }
}

void CommandGUI::dispCmd(){
  const Rect rect(x, y, x + 770, y + 430);
  const Texture rImg(rPath);
  const Texture lImg(lPath);
  const Font rUpp(50);
  const Font lUpp(50);

  rect.draw(Palette::Skyblue);

  rImg.draw(x + 510, y + 140);
  lImg.draw(x + 130, y + 140);

  rUpp(U'R').draw(x + 380, y, Palette::Black);
  lUpp(U'L').draw(x, y, Palette::Black);
}  

