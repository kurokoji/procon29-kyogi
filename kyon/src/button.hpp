#ifndef PROCON29_KYON_BUTTON_HPP_
#define PROCON29_KYON_BUTTON_HPP_

#include <Siv3D.hpp>

struct Button {
  Rect rect;
  Font font;
  Vec2 pos;

  Button();
  Button(const Rect& rect, const Font& font);
  Button(uint32 h, uint32 w);

  Button& setPos(uint32 x, uint32 y);
  Button& draw(const String& str, const ColorF& color = Palette::White);
};

#endif
