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

Game::Game() {
  turnNum = Font(20);
  turnTimes = U"";
  TurnFinish = Button(90, 60, 45, U"終");
  startButton = Button(90, 60, 45 ,U"始");
  undoButton = Button(90, 60, 45, U"戻");
  enterButton = Button(90, 30, 23, U"Enter");
  inputTurn = TextBox(turnNum, Vec2(940, 10), 200);
}

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

  std::cout << fieldData << std::endl;
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

  std::string ret;

  std::size_t sz = 0;
  do {
    asio::streambuf receive_buffer;
    sz = asio::read_until(socket, receive_buffer, "\n", err);
    ret += asio::buffer_cast<const char *>(receive_buffer.data());
  } while (sz != 0);
  socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, err);

  std::string fieldData = "";
  if (err && err != asio::error::eof) {
    std::cerr << "receive failed: " << err.message() << std::endl;
  } else {
    fieldData = ret;
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

bool Game::startGame(int32 x, int32 y) {
  startButton.setPos(x, y);
  startButton.draw();
  if (startButton.isClick()) {
    getInformation();
    return true;
  }
  return false;
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

void Game::getTurn() {
  enterButton.setPos(1145, 10);
  enterButton.draw();
  const auto result = inputTurn.update();
  inputTurn.setActive(true);
  inputTurn.draw();
  inputTurn.drawOverlay();
  if (enterButton.isClick()) {
    turnTimes = inputTurn.getText();
    Print << turnTimes;
  } else if (KeyEnter.down()) {
    turnTimes = inputTurn.getText();
    Print << turnTimes;
  }
}

}  // namespace kyon
