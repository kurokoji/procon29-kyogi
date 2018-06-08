//====================================================
//
//  mikuru
//
//  Copyright (c) 2018 Shu Kakihana
//
//  This software is released under the MIT License.
//  https://opensource.org/licenses/mit-license.php
//
//====================================================

#include <iostream>
#include <string>
#include <sstream>
#include <zbar.h>
#include <opencv2/opencv.hpp>

#include "problem_state.hpp"
#include "types.hpp"

int main(int argc, char* argv[]) {
  cv::VideoCapture cap(0);

  if (!cap.isOpened()) {
    std::cerr << "Can't open camera." << std::endl;
    std::exit(1);
  }

  zbar::ImageScanner image_scanner;
  image_scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

  mikuru::ProblemState problem;
  std::string res;
  cv::Mat frame, gray;
  while (true) {
  }
}
