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
import nagato.montecarlo,
       nagato.connection,
       nagato.color,
       nagato.state,
       nagato.util;

void main() {
  auto sc = new NagatoSocket("127.0.0.1", 20000);
  string s = sc.getProblem ~ sc.getTurn;

  State ini = State(s);
  State st = ini;
  ini.maxTurn.writeln;
  foreach (i; 0 .. 80) {
    if (i == 0) {
      i.writeln;
      import std.math : sqrt;
      auto solver = new NeoMonteCarloTreeSearch(st, 6, st.nowTurn * 2, st.maxTurn, Color.own, sqrt(2.0));
      st = solver.solve;

      sc.postAnswer(st);
      sc.postTurn(st);
      st.visualize;
    } else {
      string next = sc.getMove ~ sc.getTurn;
      st = State(next);
      i.writeln;
      import std.math : sqrt;
      auto solver = new NeoMonteCarloTreeSearch(st, 1, st.nowTurn * 2, st.maxTurn, Color.own, sqrt(2.0));
      st = solver.solve;

      sc.postAnswer(st);
      sc.postTurn(st);
      st.visualize;
    }
  }
}
