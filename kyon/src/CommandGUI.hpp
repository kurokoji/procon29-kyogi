#ifndef PROCON29_KYON_COMMAND_GUI_HPP_
#define PROCON29_KYON_COMMAND_GUI_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <Siv3D.hpp>

class CommandGUI {
  public:
    CommandGUI::CommandGUI(int32, int32);
  private:
    std::stringstream ss;
    Filepath r_path, l_path;
    int32 x, y, cmd;

    void convInt(std::string s);
    void selectImg(in32 cmd);
    void dispCmd();
};

#endif
