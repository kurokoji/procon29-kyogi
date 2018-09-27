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

module nagato.agent;

struct Agent {
  import nagato.point;
  import nagato.color : Color;

  private {
    Point!int _point;
    Color _agentTeam;
  }

  this(int y, int x, Color t) {
    _point = Point!int(y, x);
    _agentTeam = t;
  }

  this(const ref Point!int point, Color t) {
    _point = point;
    _agentTeam = t;
  }

  @property {
    Point!int point() {
      return _point;
    }

    int y() const {
      return _point.y;
    }

    int x() const {
      return _point.x;
    }

    Color agentTeam() {
      return _agentTeam;
    }
  }

  void trans(int y, int x) {
    _point += Point!int(y, x);
  }

  void trans(const ref Point!int trans) {
    _point += trans;
  }

  void trans(int n) {
    immutable int[] dy = [0, 0, -1, -1, -1, 0, 1, 1, 1];
    immutable int[] dx = [0, -1, -1, 0, 1, 1, 1, 0, -1];

    trans(dy[n], dx[n]);
  }

  void backTrans(int n) {
    immutable int[] dy = [0, 0, -1, -1, -1, 0, 1, 1, 1];
    immutable int[] dx = [0, -1, -1, 0, 1, 1, 1, 0, -1];

    trans(-dy[n], -dx[n]);
  }

  string toString() const {
    import std.format : format;

    return format("%s %s", _point.y, _point.x);
  }
}

unittest {
  import nagato.color : Color;

  auto a = Agent(1, 2, Color.own);
  a.trans(1);
  assert(a.y == 1 && a.x == 1 && a.agentTeam == Color.own);
  assert(a.toString() == "1 1");
}
