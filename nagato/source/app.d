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

import std.stdio;
import nagato.montecalro,
       nagato.connection,
       nagato.color,
       nagato.state,
       nagato.util;

void main() {
  auto sc = new NagatoSocket("127.0.0.1", 20000);
  string s = sc.getProblem ~ sc.getTurn;

  State ini = State(s);
  State st = ini;
  foreach (i; 0 .. ini.maxTurn) {
    if (i != 0) {
      string next = sc.getMove ~ sc.getTurn;
      st = State(next);
    }
    import std.math : sqrt;
    auto solver = new NeoMonteCalroTreeSearch(st, 1000, i * 2, st.maxTurn, Color.own, sqrt(2.0));
    st = solver.solve;

    sc.postAnswer(st);
    sc.postTurn(st);
    st.visualize;
  }
}
