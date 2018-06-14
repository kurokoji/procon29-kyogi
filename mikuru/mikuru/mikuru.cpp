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
#include <zbar.h>
#include <opencv2/opencv.hpp>

#include "problem_state.hpp"
#include "types.hpp"
#include "qr.hpp"

int main(int argc, char* argv[]) {
  mikuru::problem_state problem;

  std::string&& res = mikuru::get_qr_string();
  // コロンを取り除く
  std::replace(std::begin(res), std::end(res), ':', ' ');
  std::stringstream ss(res);

  std::cerr << res << std::endl;

  ss >> problem;
  std::cout << problem << std::endl;
}
