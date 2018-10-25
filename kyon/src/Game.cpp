#include "Game.hpp"

namespace kyon {

namespace tcp {
const std::string IP_ADDRESS = "127.0.0.1";
const unsigned short PORT = 20000;

namespace GET {
const std::string problem = "GET problem";
const std::string answer = "GET answer";
}  // namespace GET

namespace POST {
const std::string move = "POST move";
}  // namespace POST
}  // namespace tcp

Game::Game() : TurnFinish(90, 60, 45, U"終"), undoButton(90, 60, 45, U"戻") {}

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
  asio::read_until(socket, receive_buffer, "\n", err);
  socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, err);

  std::string fieldData = "";
  if (err && err != asio::error::eof) {
    std::cerr << "receive failed: " << err.message() << std::endl;
  } else {
    fieldData = std::string(asio::buffer_cast<const char *>(receive_buffer.data()));
  }

  return fieldData;
}

void Game::finishTurn(int32 x, int32 y) {
  TurnFinish.setPos(x, y);
  TurnFinish.draw();
  if (TurnFinish.isClick()) {
    //ここでharuhiにデータを送る
  }
}

SolverAnswer Game::getSolverAnswer() {
  namespace asio = boost::asio;
  using asio::ip::tcp;

  asio::io_service io_service;
  tcp::socket socket(io_service);
  boost::system::error_code err;

  socket.connect(tcp::endpoint(asio::ip::address::from_string(kyon::tcp::IP_ADDRESS), kyon::tcp::PORT));
  asio::write(socket, asio::buffer(kyon::tcp::GET::answer + "\n"), err);

  asio::streambuf receive_buffer;
  asio::read_until(socket, receive_buffer, "\n", err);
  socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, err);

  std::string moveDataString = "";
  if (err && err != asio::error::eof) {
    std::cerr << "receive failed: " << err.message() << std::endl;
  } else {
    moveDataString = std::string(asio::buffer_cast<const char *>(receive_buffer.data()));
  }

  std::istringstream iss(moveDataString);
  std::istream is(iss.rdbuf());

  SolverAnswer answer;
  is >> answer;

  return answer;
}

void Game::postMoveData() {
  std::string send_message = field.to_string();

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

void Game::undo(int32 x ,int32 y) {
  undoButton.setPos(x, y);
  undoButton.draw();

  if (undoButton.isClick()) {
    Print << U"hoge";
    //ここにundo動作を書く
  }
}

}  // namespace kyon
