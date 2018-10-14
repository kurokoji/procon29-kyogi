#include "Game.hpp"

namespace kyon {

namespace tcp {
namespace GET {
const std::string problem = "GET problem";
const std::string answer = "GET answer";
}  // namespace GET

namespace POST {}  // namespace POST
}  // namespace tcp

Game::Game() {
  String fieldData = getFieldData();
  std::tuple<int32, int32, Array<Array<int32>>, std::array<std::pair<size_t, size_t>, 4>> parsedFieldData = parseFieldData(fieldData);
}

void Game::update() {
  ;
}

void Game::draw() {
  this->fs.draw();
}

String Game::getFieldData() {
  namespace asio = boost::asio;
  using asio::ip::tcp;

  asio::io_service io_service;
  tcp::socket socket(io_service);
  boost::system::error_code err;

  const std::string IP_ADDRESS = "127.0.0.1";
  const unsigned short PORT = 20000;

  socket.connect(tcp::endpoint(asio::ip::address::from_string(IP_ADDRESS), PORT));
  asio::write(socket, asio::buffer(kyon::tcp::GET::problem + "\n"), err);

  asio::streambuf receive_buffer;
  asio::read(socket, receive_buffer, asio::transfer_all(), err);

  String fieldData = U"";
  if (err && err != asio::error::eof) {
    std::cerr << "recieve failed: " << err.message() << std::endl;
  } else {
    fieldData = s3d::Unicode::Widen(std::string(asio::buffer_cast<const char *>(receive_buffer.data())));
  }

  return fieldData;
}

std::tuple<int32, int32, Array<Array<int32>>, std::array<std::pair<size_t, size_t>, 4>> Game::parseFieldData(const String &fieldData) {
  std::stringstream ss;
  std::string line;

  ss << fieldData;
  std::getline(ss, line);

  int32 h, w;
  Array<Array<int32>> fieldPoints;
  std::array<std::pair<size_t, size_t>, 4> positions;
  std::stringstream ssLine;

  ssLine << line;
  ssLine >> h >> w;

  for (int i = 0; i < h; i++) {
    Array<int32> v;
    std::stringstream sLine;
    std::getline(ss, line);
    sLine << line;

    while (!sLine.eof()) {
      int32 tmp;
      sLine >> tmp;
      v.emplace_back(tmp);
    }
    fieldPoints.emplace_back(v);
  }

  for (int i = 0; i < 4; i++) {
    int y, x;
    std::stringstream sLine;
    std::getline(ss, line);
    sLine << line;
    sLine >> y >> x;
    positions[i] = std::make_pair(y, x);
  }

  return {h, w, fieldPoints, positions};
}

}  // namespace kyon
