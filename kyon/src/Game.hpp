#ifndef PROCON29_KYON_GAME_HPP_
#define PROCON29_KYON_GAME_HPP_

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include "button.hpp"

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

    std::tuple<int32, int32, std::vector<std::vector<int32>>> parseFieldData(const String& fieldData) {
        std::stringstream ss;
        std::string line;

        ss << fieldData;
        std::getline(ss, line);

        int32 h, w;
        std::stringstream ssLine;
        std::vector<std::vector<int32>> fieldPoints;

        ssLine << line;
        ssLine >> h >> w;

        while (std::getline(ss, line)) {
            std::vector<int32> v;
            ssLine << line;

            while (!ssLine.eof()) {
                int32 tmp;
                ssLine >> tmp;
                v.push_back(tmp);
            }
            fieldPoints.push_back(v);
        }

        return std::make_tuple(h, w, fieldPoints);
    }
};

#endif