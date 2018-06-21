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

#ifndef PROCON29_MIKURU_COLOR_HPP_
#define PROCON29_MIKURU_COLOR_HPP_

namespace mikuru {
/*
 * BLANK(0) -> まだ埋められていない
 * BLUE(1) -> 自チームのマス
 * RED(2) -> 相手チームのマス
 */
enum class color { BLANK, BLUE, RED };
}  // namespace mikuru

#endif
