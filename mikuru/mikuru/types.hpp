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

#ifndef MIKURU_TYPES_H_
#define MIKURU_TYPES_H_

#include <cstdint>
namespace mikuru {
/*
 * Integer types
 */

using int8 = std::int_fast8_t;
using int16 = std::int_fast16_t;
using int32 = std::int_fast32_t;
using int64 = std::int_fast64_t;

/*
 * Character types
 */

using char8 = char;
using char16 = char16_t;
using char32 = char32_t;

/*
 * Score type
 */

using score_type = int32;
} // namespace mikuru

#endif
