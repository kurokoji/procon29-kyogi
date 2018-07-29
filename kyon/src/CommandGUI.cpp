#include "CommandGUI.hpp"
#include <Siv3D.hpp>

CommandGUI::CommandGUI(int32 rec_x, int32 rec_y){
  x = rec_x;
  y = rec_y;
}

void CommandGUI::convInt(std::string s){
  ss << s;
  ss >> cmd;
}

void CommandGUI::selectImg(int32 cmd){
  switch(cmd){
    case 0:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    case 1:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    case 2:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    case 3:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    case 4:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    case 5:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    case 6:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    case 7:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    case 8:
      r_path = path_to_img;
      l_path = path_to_img;
      break;
    default:
      break;
  }
}

void CommandGUI::dispCmd(){
  const Rect rect();
  const Texture r_img(r_path);
  const Texture l_img(l_path);
  const Font r_upp();
  const Font l_upp();

  rect().draw();
  
  r_img.draw();
  l_img.draw();

  r_upp.draw();
  l_upp.draw();
}  

