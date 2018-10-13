#include "Field.hpp"
#include <Siv3D.hpp>

namespace kyon {

Field::Field(int32 h, int32 w) : squSize(60), H(h), W(w), image(h, w, Palette::White), texture(image) {}


void Field::InitField() {
  //Agentの位置をfieldSquareに渡す
  //各マスに割り振られた点数をfieldSquareに渡す
}

//fieldの更新
void Field::updateField() {
  //drawされたfieldSquareに変化がある場合(clickされたとき)に呼び出される
  //マスの色の変化をupdateする
}

//H * W　マスの描画
void Field::drawField(const String &str, bool &hasAgent) {
  texture.scaled(squSize).draw(10, 10);

  for (int i : step(H)) {
    for (int j : step(W)) {
      square[i][j].setPos(10 + j * squSize, 10 + i * squSize);
      square[i][j].draw(str, hasAgent);
      square[i][j].rect.drawFrame(1.0, 1.0, Palette::Gray);

      texture.fill(image);
    }
  }
//  updateField();
}

}
