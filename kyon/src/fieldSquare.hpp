#include "button.hpp"

class FieldSquare : public Button {
public:
  //updateでの色選択用
  Rect choiceWhiteSquare;
  Rect choiceRedSquare;
  Rect choiceBlueSquare;
  //エージェントの有無を表す
  Circle agentMarker;
  //色選択用のRectを表示するかしないか
  bool isSquareDisp;
  //色選択用のRectの表示をキャンセルできるかできないか
  bool canCancel;
  //マスが何色かの判定
  int32 whatColor;
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
  FieldSquare& draw(const String& str, bool& hasAgent);
  //赤チームの選択肢を表示
  void choiceRedTeam();
  //青チームの選択肢を表示
  void choiceBlueTeam();
  //白を選択した場合
  void choiceWhite();
  //選択肢の非表示
  void dispCancel();
  //whatColorに合わせてマスの色を描画
  void normalSquare();
  //マスをクリックしたときの挙動
  void update(const String& whichAgent);
  void update(const String&& whichAgent);
  //行動できる場所へ矢印を表示する
  void dispArrow(int32 solverDirection, bool canMove[]);
};
