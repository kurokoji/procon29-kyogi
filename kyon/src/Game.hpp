#ifndef PROCON29_KYON_GAME_HPP_
#define PROCON29_KYON_GAME_HPP_

#include <Siv3D.hpp>
#include <HamFramework.hpp>

// 全てのシーンからアクセスできるデータ
// getData().memberNameで利用できる
struct GameData {
    // int32 memberName = 0;
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

    String getFieldData() {
        // tcp通信で持ってくる
        const String fieldData = U"8 8\n \
                            1 2 3 4 4 3 2 1\n \
                            2 3 4 5 5 4 3 3\n \
                            3 4 5 6 6 5 4 3\n \
                            4 5 6 7 7 6 5 4\n \
                            4 5 6 7 7 6 5 4\n \
                            3 4 5 6 6 5 4 3\n \
                            2 3 4 5 5 4 3 2\n \
                            1 2 3 4 4 3 2 1";
        
        return fieldData;
    }
};

#endif