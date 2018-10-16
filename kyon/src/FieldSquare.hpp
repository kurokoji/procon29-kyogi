#ifndef PROCON29_KYON_FIELD_SQUARE_HPP_
#define PROCON29_KYON_FIELD_SQUARE_HPP_

#include "Button.hpp"
#include "Color.hpp"

namespace kyon {
class FieldSquare : public Button {
public:
  //どのエージェントがマスにいるかの判断
  int32 onAgent; //0はなし,1はb1,2はb2,3はr1,4はr2です
  //マスの点数
  String squareNum;
  //updateでの色選択用
  Rect choiceColor;
  //エージェントの有無を表す
  Circle agent1Marker;
  Triangle agent2Marker;
  //色選択用のRectを表示するかしないか
  bool isSquareDisp;
  //色選択用のRectの表示をキャンセルできるかできないか
  bool canCancel;
  //マスが何色かの判定
  Color whatColor;
  //矢印関連
  Texture solverArrow;
  Texture normalArrow;
  FilePath solverArrowPath;
  FilePath normalArrowPath;
  int32 arrowX[8];
  int32 arrowY[8];

  FieldSquare();
  //座標設定
  FieldSquare& setPos(uint32 x, uint32 y);
  //マスを表示
  FieldSquare& draw();
  //選択肢の非表示
  void dispCancel();
  //whatColorに合わせてマスの色を描画
  void normalSquare();
  //マスをクリックしたときの挙動
  void update(const String whichAgent);
  //行動できる場所へ矢印を表示する
  void dispArrow(int32 solverDirection, bool canMove[]);
};
}

#endif
