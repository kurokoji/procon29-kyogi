#ifndef PROCON29_KYON_GAME_HPP_
#define PROCON29_KYON_GAME_HPP_

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "button.hpp"

namespace kyon {

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
        Game(const InitData &init) : IScene(init) {}

        void update() override;

//    void draw() const override {
//        Rect(120, 120, 40, 40).draw();
//    }
        void draw() const override;

        String getFieldData();

        std::tuple<int32, int32, std::vector<std::vector<int32>>> parseFieldData(const String &fieldData);
    };

}

#endif
