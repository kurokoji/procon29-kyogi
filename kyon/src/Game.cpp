#include "Game.hpp"

namespace kyon {
extern bool colorRev;
namespace tcp {
const std::string IP_ADDRESS = "127.0.0.1";
const unsigned short PORT = 20000;

namespace GET {
const std::string problem = "GET problem";
const std::string answer = "GET answer";
const std::string turn = "GET turn";
}  // namespace GET

namespace POST {
const std::string move = "POST move";
const std::string turn = "POST turn";
}  // namespace POST
}  // namespace tcp

Game::Game() {
  turnNum = Font(20);
  pointSumLabel = Font(41);
  turnLabel = Font(41);
  nowTurn = U"0";
  maxTurn = U"80";
  TurnFinish = Button(90, 60, 45, U"終");
  startButton = Button(90, 60, 45 ,U"始");
  undoButton = Button(90, 60, 45, U"戻");
  toggleColorButton = Button(90, 30, 23, U"青チーム");
  enterButton = Button(90, 30, 23, U"Enter");
  inputTurn = TextBox(turnNum, Vec2(940, 10), 200);
}

void Game::getInformation() {
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

  std::string str_fieldData = getFieldData();
  if (str_fieldData != "") {
    std::istringstream iss(str_fieldData);
    std::istream is(iss.rdbuf());
    is >> problemState;
    field.InitData(problemState);
    field.InitField();
  }
}

void Game::update() {
  ;
}

void Game::draw() {
  auto sa = getSolverAnswer();
  field.drawField(sa.blue);
  getTurnData();
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

  if (ret.substr(0, 2) == "NG") {
    return "";
  }

  std::string fieldData = "";
  if (err && err != asio::error::eof) {
    std::cerr << "receive failed: " << err.message() << std::endl;
    return "";
  } else {
    fieldData = ret;
  }

  return fieldData;
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

  if (moveDataString.substr(0, 2) == "NG") {
    return solverAnswer;
  }

  std::istringstream iss(moveDataString);
  std::istream is(iss.rdbuf());

  SolverAnswer answer;
  is >> answer;

  solverAnswer = answer;

  return answer;
}

void Game::getTurnData() {
  namespace asio = boost::asio;
  using asio::ip::tcp;

  asio::io_service io_service;
  tcp::socket socket(io_service);
  boost::system::error_code err;

  socket.connect(tcp::endpoint(asio::ip::address::from_string(kyon::tcp::IP_ADDRESS), kyon::tcp::PORT));
  asio::write(socket, asio::buffer(kyon::tcp::GET::turn + "\n"), err);

  std::string ret;

  std::size_t sz = 0;
  do {
    asio::streambuf receive_buffer;
    sz = asio::read_until(socket, receive_buffer, "\n", err);
    ret += asio::buffer_cast<const char *>(receive_buffer.data());
  } while (sz != 0);
  socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, err);

  if (ret.substr(0, 2) == "NG") {
    return;
  }

  if (err && err != asio::error::eof) {
    std::cerr << "receive failed: " << err.message() << std::endl;
  } else {
    std::istringstream iss(ret);
    std::istream is(iss.rdbuf());

    is >> nowTurn >> maxTurn;
  }
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
    std::cerr << "[POST move send failed] " << err.message() << std::endl;
  } else {
    asio::write(socket, asio::buffer(send_message), err);
  }
}

void Game::postTurnData() {
  std::string send_message = nowTurn.narrow() + " " + maxTurn.narrow() + "\n";

  namespace asio = boost::asio;
  using asio::ip::tcp;

  asio::io_service io_service;
  tcp::socket socket(io_service);
  boost::system::error_code err;

  socket.connect(tcp::endpoint(asio::ip::address::from_string(kyon::tcp::IP_ADDRESS), kyon::tcp::PORT));
  asio::write(socket, asio::buffer(kyon::tcp::POST::turn + "\n"), err);

  if (err && err != asio::error::eof) {
    std::cerr << "[POST turn send failed] " << err.message() << std::endl;
  } else {
    asio::write(socket, asio::buffer(send_message), err);
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

void Game::finishTurn(int32 x, int32 y) {
  TurnFinish.setPos(x, y);
  TurnFinish.draw();
  if (TurnFinish.isClick()) {
    field.prev = field.squares;
    problemState.fieldColor = field.fColor;
    problemState.blue = field.bluePos;
    problemState.red = field.redPos;

    //ここでharuhiにデータを送る
    postMoveData();

    // turnのデータをpostする

    field.b1DispArrow = true;
    field.b2DispArrow = true;
  }
}

void Game::undo(int32 x ,int32 y) {
  undoButton.setPos(x, y);
  undoButton.draw();

  if (undoButton.isClick()) {
    field.squares = field.prev;
    field.fColor = problemState.fieldColor;
    field.bluePos = problemState.blue;
    field.redPos = problemState.red;
    field.b1DispArrow = true;
    field.b2DispArrow = true;
  }
}


void Game::toggleColor(int32 x, int32 y) {
  if (toggleColorButton.isClick()) {
    colorRev = !colorRev;
    toggleColorButton.rectStr = toggleColorButton.rectStr == U"青チーム" ? U"赤チーム" : U"青チーム";
  }
  toggleColorButton.setPos(x, y);
  toggleColorButton.draw();
}

void Game::getTurn() {
  enterButton.setPos(1145, 10);
  enterButton.draw();
  const auto result = inputTurn.update();
  inputTurn.setActive(true);
  inputTurn.draw();
  inputTurn.drawOverlay();
  if (enterButton.isClick() || KeyEnter.down()) {
    maxTurn = inputTurn.getText();
    postTurnData();
  }
}

void Game::pointSum(int32 x, int32 y) {
  auto [blue, red] = field.countPoint();
  pointSumLabel(U"自{} vs {}相"_fmt(blue, red)).draw(x, y, Palette::Black);
}

void Game::dispTurn(int32 x, int32 y) {
  turnLabel(U"現在のターン: {}"_fmt(nowTurn)).draw(x, y, Palette::Black);
}

}  // namespace kyon
