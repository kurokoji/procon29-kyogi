#ifndef PROCON29_KYON_COMMAND_GUI_HPP_
#define PROCON29_KYON_COMMAND_GUI_HPP_

#include <Siv3D.hpp>

namespace kyon {
class CommandGUI {
public:
  CommandGUI();
  CommandGUI(int32, int32);
  void selectImg(int32, int32);
  void dispCmd(int32, int32);

private:
  FilePath nemu, higashi;
  int32 x, y;
};
} // namespace kyon

#endif
