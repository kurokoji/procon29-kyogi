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

#include "qr.hpp"
#include "types.hpp"
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <zbar.h>
#include <opencv2/opencv.hpp>

namespace mikuru {
std::string get_qr_string(size_t cam_num) {
  cv::VideoCapture cap(0);

  if (!cap.isOpened()) {
    std::cerr << "Can't open camera." << std::endl;
    std::exit(1);
  }

  zbar::ImageScanner image_scanner;
  image_scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

  std::string res;
  cv::Mat frame, gray;
  while (true) {
    cap >> frame;
    cv::imshow("Camera", frame);

    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    cv::cvtColor(frame, gray, cv::COLOR_RGB2GRAY);

    size_t const width = frame.cols, height = frame.rows;
    auto const raw = gray.data;

    zbar::Image zbar_image(width, height, "Y800", raw, width * height);
    size_t const symbol_num = image_scanner.scan(zbar_image);

    auto get_symbol = [&]() -> bool {
      for (auto itr = zbar_image.symbol_begin(); itr != zbar_image.symbol_end();
           ++itr) {
        res = itr->get_data();
        return true;
      }
      return false;
    };

    // QRコードがあった場合はbreak
    if (symbol_num && get_symbol())
      break;

    // 'q'が押された場合はbreak
    mikuru::int32 const key = cv::waitKey(60);
    if (key == 'q')
      break;
  }

  if (res == "") {
    std::cerr << "Empty result." << std::endl;
    std::exit(1);
  }

  return res;
}
} // namespace mikuru
