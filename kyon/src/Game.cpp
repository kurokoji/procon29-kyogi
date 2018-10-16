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
  std::string fieldData = getFieldData();
  std::istringstream iss(fieldData);
  std::istream is(iss.rdbuf());
  is >> problemState;
}

void Game::update() {
  ;
}

void Game::draw() {
  this->fs.draw();
}

std::string Game::getFieldData() {
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

  std::string fieldData = "";
  if (err && err != asio::error::eof) {
    std::cerr << "recieve failed: " << err.message() << std::endl;
  } else {
    fieldData = std::string(asio::buffer_cast<const char *>(receive_buffer.data()));
  }

  return fieldData;
}

}  // namespace kyon
