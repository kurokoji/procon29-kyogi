//====================================================
//
//  nagato
//
//  Copyright (c) 2018 Shu Kakihana
//
//  This software is released under the GNU General Public License version 3.
//  https://opensource.org/licenses/GPL-3.0
//
//====================================================

#ifndef NAGATO_TYPES_HPP_
#define NAGATO_TYPES_HPP_

#include <cstdint>
#include <cmath>

namespace nagato {
/*
 * Integer types
 */

using i8 = std::int_fast8_t;
using i16 = std::int_fast16_t;
using i32 = std::int_fast32_t;
using i64 = std::int_fast64_t;

/*
 * Character types
 */

using c8 = char;
using c16 = char16_t;
using c32 = char32_t;

/*
 * Score type
 */

using score_type = i64;
} // namespace nagato

#endif
