#ifndef PROCON29_KYON_COMMAND_GUI_HPP_
#define PROCON29_KYON_COMMAND_GUI_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <Siv3D.hpp>

namespace kyon {
class CommandGUI {
public:
    CommandGUI(int32, int32); 
    void convInt(std::string);
    void selectImg(int32);
    void dispCmd();
private:
    std::stringstream ss;
    FilePath rPath, lPath;
    int32 x, y, cmd;
};
}

#endif
