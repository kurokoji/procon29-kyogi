#ifndef COMMAND_GUI_HPP
#define COMMAND_GUI_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <Siv3D.hpp>

class Command_gui {
  public:
    Command_gui::Command_gui(int32 rect_x, int32 rect_y){
    }
  private:
    std::stringstream ss;
    Filepath r_path, l_path;
    int32 x, y, cmd;

    void conv_int(std::string s);
    void select_img(in32 cmd);
    void disp_cmd();
};

#endif
