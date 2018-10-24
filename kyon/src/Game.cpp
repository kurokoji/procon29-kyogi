#include "Game.hpp"

namespace kyon {

namespace tcp {
const std::string IP_ADDRESS = "127.0.0.1";
const unsigned short PORT = 20000;

namespace GET {
const std::string problem = "GET problem";
const std::string answer = "GET answer";
}  // namespace GET

namespace POST {  // namespace POST
const std::string move = "POST move";
}
}  // namespace tcp

void Game::getInformation() {
  // getFieldData() でharuhi(server)に取りにいく
  std::string fieldData = getFieldData();

  // haruhi(server)を動かさないでやるときはコメントアウトを外す
/*
  std::string fieldData = "4 4\
                           1 2 2 1\
                           2 3 3 2\
                           2 3 3 2\
                           1 2 2 1\
                           1 1\
                           2 2\
                           1 2\
                           2 1";
*/

  std::istringstream iss(fieldData);
  std::istream is(iss.rdbuf());
  is >> problemState;
  field.InitData(problemState);
  field.InitField();
}

void Game::update() {
  ;
}

void Game::draw() {
  field.drawField();
}

std::string Game::getFieldData() {
  namespace asio = boost::asio;
  using asio::ip::tcp;

  asio::io_service io_service;
  tcp::socket socket(io_service);
  boost::system::error_code err;

  socket.connect(tcp::endpoint(asio::ip::address::from_string(kyon::tcp::IP_ADDRESS), kyon::tcp::PORT));
  asio::write(socket, asio::buffer(kyon::tcp::GET::problem + "\n"), err);

  asio::streambuf receive_buffer;
  asio::read(socket, receive_buffer, asio::transfer_all(), err);

  std::string fieldData = "";
  if (err && err != asio::error::eof) {
    std::cerr << "receive failed: " << err.message() << std::endl;
  } else {
    fieldData = std::string(asio::buffer_cast<const char *>(receive_buffer.data()));
  }

  return fieldData;
}

void Game::postMoveData(MoveData& moveData) {
  std::string send_message = moveData.to_string();

  namespace asio = boost::asio;
  using asio::ip::tcp;

  asio::io_service io_service;
  tcp::socket socket(io_service);
  boost::system::error_code err;

  socket.connect(tcp::endpoint(asio::ip::address::from_string(kyon::tcp::IP_ADDRESS), kyon::tcp::PORT));
  asio::write(socket, asio::buffer(kyon::tcp::POST::move + "\n"), err);

  if (err && err != asio::error::eof) {
    std::cerr << "send failed: " << err.message() << std::endl;
  } else {
    asio::write(socket, asio::buffer(send_message), err);
  }
}

}  // namespace kyon
