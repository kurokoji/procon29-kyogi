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

module nagato.util.visualizer;

import nagato.state;

/// CUIで結果のvisualize
void visualize(ref State st) {
  import std.format : format;

  string res;
  with (st) {
    immutable auto height = field.height;
    immutable auto width = field.width;

    res ~= '┌';
    foreach (i; 0 .. width) {
      res ~= format("───%s", i != width - 1 ? '┬' : '┐');
    }
    res ~= '\n';

    foreach (i; 0 .. height) {
      res ~= '│';
      foreach (j; 0 .. width) {
        import nagato.color : Color;
        immutable auto agentColor = st.agentExists(i, j);
        immutable auto color = st.fieldState.getColor(i, j);
        immutable auto score = st.field.getScore(i, j);

        uint textAttribute, backgroundColor;

        // text
        textAttribute = agentColor == Color.none ? 0 : 4;

        // back
        if (color == Color.own) {
          backgroundColor = 41;
        } else if (color == Color.opponent) {
          backgroundColor = 44;
        } else {
          backgroundColor = 40;
        }


        res ~= format("\x1b[%s;%sm%3s\x1b[m%s", textAttribute, backgroundColor, score, '│');
      }

      res ~= '\n';

      if (i != height - 1) {
        res ~= '├';
        foreach (j; 0 .. width) {
          res ~= format("───%s", j != width - 1 ? '┼' : '┤');
        }
      } else {
        res ~= '└';
        foreach (j; 0 .. width) {
          res ~= format("───%s", j != width - 1 ? '┴' : '┘');
        }
      }
      res ~= '\n';
    }
  }

  import std.stdio : write, writefln;
  write(res);

  immutable auto sc = st.getScoreSum();
  writefln("Red: %s, Blue: %s", sc.own, sc.opponent);
}
