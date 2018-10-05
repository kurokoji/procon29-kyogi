#include "Game.hpp"

namespace kyon {

namespace tcp {
namespace GET {
const std::string problem = "GET problem";
const std::string answer = "GET answer";
}  // namespace GET

namespace POST {}  // namespace POST
}  // namespace tcp

void Game::update() {
  ;
}

void Game::draw() {
  String s = U"hoge";
  bool f = false;
  this->fs.draw(s, f);
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