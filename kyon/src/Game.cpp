#include "Game.hpp"
#include <Siv3D.hpp>

namespace kyon {

void Game::update() {
  ;
}

void Game::draw() const {
  Rect(120, 120, 40, 40).draw();
}

String Game::getFieldData() {
  // tcp通信で持ってくる
  const String fieldData =
      U"8 8\n \
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

std::tuple<int32, int32, std::vector<std::vector<int32>>> Game::parseFieldData(const String &fieldData) {
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

  return {h, w, fieldPoints};
}

}  // namespace kyon