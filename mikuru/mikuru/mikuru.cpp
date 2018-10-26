//====================================================
//
//  mikuru
//
//  Copyright (c) 2018 Shu Kakihana
//
//  This software is released under the GNU General Public License version 3.
//  https://opensource.org/licenses/GPL-3.0
//
//====================================================

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <zbar.h>
#include <opencv2/opencv.hpp>

#include "problem_state.hpp"
#include "types.hpp"
#include "qr.hpp"

#include <boost/asio.hpp>

namespace mikuru {
namespace tcp {
namespace GET {
const std::string problem = "GET problem";
const std::string answer = "GET answer";
}  // namespace GET

namespace POST {
const std::string problem = "POST problem";
const std::string answer = "POST answer";
}  // namespace POST
}  // namespace tcp
}  // namespace mikuru

int main(int argc, char* argv[]) {
  std::string ip_address = "127.0.0.1";
  mikuru::int32 port = 20000;
  if (argc > 2) {
    ip_address = argv[1];
    port = std::atoi(argv[2]);
  }

  namespace asio = boost::asio;
  using asio::ip::tcp;

  mikuru::problem_state problem;

  std::string&& res = mikuru::get_qr_string();
  // コロンを取り除く
  std::replace(std::begin(res), std::end(res), ':', ' ');
  std::stringstream ss(res);

  std::cerr << res << std::endl;

  ss >> problem;

  ss << problem;

  // TCP通信(送信)

  asio::io_service io_service;
  tcp::socket socket(io_service);
  boost::system::error_code err;

  socket.connect(tcp::endpoint(asio::ip::address::from_string(ip_address), port));

  asio::write(socket, asio::buffer(mikuru::tcp::POST::problem + "\n"), err);

  std::string send_message = ss.str();

  std::cout << send_message << std::endl;

  if (!err) {
    asio::write(socket, asio::buffer(send_message), err);
  }
}
