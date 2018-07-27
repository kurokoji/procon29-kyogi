#include "button.hpp"
#include <Siv3D.hpp>

Button::Button() : rect(0, 0, 60, 60), font(40), pos(60, 60) {}
Button::Button(const Rect& rect, const Font& font) : rect(rect), font(font) {}
Button::Button(uint32 h, uint32 w) : rect(0, 0, h, w), font(40), pos(h, w) {}

Button& Button::setPos(uint32 x, uint32 y) {
    pos = Vec2(x, y);
    rect.setPos(x, y);
    //font.draw(x, y, Palette::White);
    return *this;
}

Button& Button::draw(const String& str, const ColorF& color) {
    rect.draw(color);
    font(str).draw(pos, Palette::White);
    return *this;
}

