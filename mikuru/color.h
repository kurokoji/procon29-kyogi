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

#ifndef MIKURU_COLOR_H
#define MIKURU_COLOR_H

namespace mikuru {
/*
 * BLANK(0) -> まだ埋められていない
 * BLUE(1) -> 自チームのマス
 * RED(2) -> 相手チームのマス
 */
enum class Color { BLANK, BLUE, RED };
} // namespace mikuru

#endif
