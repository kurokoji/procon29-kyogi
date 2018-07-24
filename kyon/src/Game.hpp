#ifndef PROCON29_KYON_Game_HPP_
#define PROCON29_KYON_Game_HPP_
#endif

#include <Siv3D.hpp>
#include <HamFramework.hpp>

// 全てのシーンからアクセスできるデータ
// getData().memberNameで利用できる
struct GameData {
    int32 hoge = 0;
};

using App = SceneManager<String, GameData>;

class Game : public App::Scene {
public:
    // // destructor
    // virtual ~Game() = default;

    // // constructor
    Game(const InitData& init): IScene(init) {}

    void update() override {
        ;
    }

    void draw() const override {
        Rect(120, 120, 40, 40).draw();
    }
};
