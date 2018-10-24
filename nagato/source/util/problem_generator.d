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

module nagato.util.problem_generator;

string generateProblem() {
  import std.random : Xorshift, unpredictableSeed, dice, choice;
  import std.range : iota;
  import std.typecons : tuple, Tuple;
  import std.format : format;

  auto rnd = Xorshift(unpredictableSeed);

  auto sizeRange = iota(9, 13);
  auto pointPlusRange = iota(1, 17);
  auto pointMinusRange = iota(-16, 1);
  auto whichSymmetry = iota(0, 3).choice(rnd);
  uint h, w;

  // マスの最小数は80
  for (h = sizeRange.choice(rnd), w = sizeRange.choice(rnd); h * w < 80;) {}

  int[][] field = new int[][](h, w);
  Tuple!(int, "y", int, "x")[4] agents;
  auto heightAgentRange = iota(0, h / 2),
       widthAgentRange = iota(0, w / 2);

  agents[0] = tuple!("y", "x")(heightAgentRange.choice(rnd), widthAgentRange.choice(rnd));
  agents[1] = tuple!("y", "x")(h - 1 - agents[0].y, w - 1 - agents[0].x);
  agents[2] = tuple!("y", "x")(h - 1 - agents[0].y, agents[0].x);
  agents[3] = tuple!("y", "x")(agents[0].y, w - 1 - agents[0].x);

  switch (whichSymmetry) {
  default:
    break;
  case 0:
    foreach (i; 0 .. h / 2) {
      foreach (j; 0 .. w / 2) {
        auto isPlus = cast(bool)rnd.dice(10, 90);
        field[i][j] = isPlus ? pointPlusRange.choice(rnd) : pointMinusRange.choice(rnd);
        field[h - 1 - i][j] = field[i][j];
        field[i][w - 1 - j] = field[i][j];
        field[h - 1 - i][w - 1 - j] = field[i][j];
      }
    }

    if (h & 1) {
      foreach (i; 0 .. w / 2) {
        auto isPlus = cast(bool)rnd.dice(10, 90);
        field[h / 2][i] = isPlus ? pointPlusRange.choice(rnd) : pointMinusRange.choice(rnd);
        field[h / 2][w - 1 - i] = field[h / 2][i];
      }
    }
    if (w & 1) {
      foreach (i; 0 .. h / 2) {
        auto isPlus = cast(bool)rnd.dice(10, 90);
        field[i][w / 2] = isPlus ? pointPlusRange.choice(rnd) : pointMinusRange.choice(rnd);
        field[h - 1 - i][w / 2] = field[i][w / 2];
      }
    }
    if (h & 1 && w & 1) {
      auto isPlus = cast(bool)rnd.dice(10, 90);
      field[h / 2][w / 2] = isPlus ? pointPlusRange.choice(rnd) : pointMinusRange.choice(rnd);
    }
    break;
  case 1:
    foreach (i; 0 .. h) {
      foreach (j; 0 .. w / 2) {
        auto isPlus = cast(bool)rnd.dice(10, 90);
        field[i][j] = isPlus ? pointPlusRange.choice(rnd) : pointMinusRange.choice(rnd);
        field[i][w - 1 - j] = field[i][j];
      }
    }

    if (w & 1) {
      foreach (i; 0 .. h) {
        auto isPlus = cast(bool)rnd.dice(10, 90);
        field[i][w / 2] = isPlus ? pointPlusRange.choice(rnd) : pointMinusRange.choice(rnd);
      }
    }
    break;
  case 2:
    foreach (i; 0 .. h / 2) {
      foreach (j; 0 .. w) {
        auto isPlus = cast(bool)rnd.dice(10, 90);
        field[i][j] = isPlus ? pointPlusRange.choice(rnd) : pointMinusRange.choice(rnd);
        field[h - 1 - i][j] = field[i][j];
      }
    }

    if (h & 1) {
      foreach (i; 0 .. w) {
        auto isPlus = cast(bool)rnd.dice(10, 90);
        field[h / 2][i] = isPlus ? pointPlusRange.choice(rnd) : pointMinusRange.choice(rnd);
      }
    }
    break;
  }

  string ret;

  ret ~= format("%s %s\n", h, w);
  foreach (i; 0 .. h) {
    foreach (j; 0 .. w) {
      ret ~= format("%s%s", field[i][j], j == w - 1 ? '\n' : ' ');
    }
  }
  foreach (const ref e; agents[]) {
    ret ~= format("%s %s\n", e.y, e.x);
  }

  return ret;
}
