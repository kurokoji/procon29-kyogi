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

module nagato.util.judge;

import nagato.color;
import nagato.state;

Color judge(State st) {
  auto res = st.getScoreSum();

  if (res.own > res.opponent) {
    return Color.own;
  } else if (res.own < res.opponent) {
    return Color.opponent;
  }
  
  return Color.none;
}
