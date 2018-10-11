#ifndef PROCON29_KYON_BUTTON_HPP_
#define PROCON29_KYON_BUTTON_HPP_

#include <Siv3D.hpp>

namespace kyon {
struct Button {
  Rect rect;
  Font font;
  Vec2 pos;
  uint32 clickNum = 0;

  Button();
  Button(const Rect& rect, const Font& font);
  Button(uint32 h, uint32 w);

  //座標設定
  Button& setPos(uint32 x, uint32 y);
  //マスの描画
  Button& draw(const String& str);
  //クリックした際の挙動
  void update();
};
}

#endif
