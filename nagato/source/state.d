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

module nagato.state;

struct State {
  import nagato.field;
  import nagato.agent;
  import nagato.field_state;
  import nagato.point;
  import nagato.color : Color;
  import std.typecons : Tuple, tuple;

  alias ScoreType = int;
  private {
    Field!ScoreType _field;
    FieldState _fieldState;
    Agent[2] _own, _opponent;
    int[4] _agentVec;
  }

  this(ref in string s) {
    import std.conv : to;
    import std.algorithm : map;
    import std.string : split;
    import nep.scanner;

    auto sc = new Scanner(s);
    int h, w;
    sc.scan(h, w);

    _fieldState = FieldState(h, w);

    ScoreType[][] ar = new ScoreType[][](h, w);

    foreach (i; 0 .. h) {
      ar[i] = sc.nextArray!ScoreType(w);
    }

    _field = Field!ScoreType(h, w, ar);

    foreach (i; 0 .. h) {
      foreach (j; 0 .. w) {
        _fieldState.changeColor(i, j, cast(Color)sc.next!int);
      }
    }

    foreach (ref e; _own) {
      int y, x;
      sc.scan(y, x);
      e = Agent(y, x, Color.own);
      _fieldState.changeColor(y, x, Color.own);
    }

    foreach (ref e; _opponent) {
      int y, x;
      sc.scan(y, x);
      e = Agent(y, x, Color.opponent);
      _fieldState.changeColor(y, x, Color.opponent);
    }

  }

  this(this) {
    _own = _own.dup;
    _opponent = _opponent.dup;
  }

  ref State opAssign(ref State s) {
    _field = s.field;
    _fieldState = s.fieldState;
    _own = s.own.dup;
    _opponent = s.opponent.dup;
    _agentVec = s.agentVec.dup;
    return this;
  }

  ref State opAssign(State s) {
    _field = s.field;
    _fieldState = s.fieldState;
    _own = s.own.dup;
    _opponent = s.opponent.dup;
    _agentVec = s.agentVec.dup;
    return this;
  }

  @property {
    ref inout(FieldState) fieldState() inout {
      return _fieldState;
    }

    ref inout(Field!ScoreType) field() inout {
      return _field;
    }

    ref inout(Agent[2]) own() inout {
      return _own;
    }

    ref inout(Agent[2]) opponent() inout {
      return _opponent;
    }

    ref inout(int[4]) agentVec() inout {
      return _agentVec;
    }
  }

  /+
    与えられた座標にAgentが存在するか
    存在する場合，そのエージェントの列挙型Colorの値が返る
    存在しない場合，SquareColor.noneが返る
    +/
  Color agentExists(int ny, int nx) const {
    auto point = Point!int(ny, nx);
    foreach (e; _own ~ _opponent) {
      if (e.point == point) {
        return e.agentTeam;
      }
    }

    return Color.none;
  }

  /+ ditto +/
  Color agentExists(ref in Point!int point) const {
    foreach (e; _own ~ _opponent) {
      if (e.point == point) {
        return e.agentTeam;
      }
    }

    return Color.none;
  }

  // 正しい状態か
  bool isValidState() const {
    bool[Point!int] dic;

    foreach (e; _own ~ _opponent) {
      // field内にagentがいるかどうか
      if (!isInside(e.point))
        return false;

      // agentが立っている場所が相手チームのマスではないか
      if (e.agentTeam != _fieldState.getColor(e.y, e.x) && e.agentTeam != Color.none)
        return false;

      dic[e.point] = true;
    }

    // 複数のagentが同じマスにいないか
    if (dic.length != 4)
      return false;

    return true;
  }

  bool isInside(Point!int p) const {
    return 0 <= p.y && p.y < _field.height && 0 <= p.x && p.x < _field.width;
  }

  bool isInside(int y, int x) const {
    return 0 <= y && y < _field.height && 0 <= x && x < _field.width;
  }

  Tuple!(ScoreType, "own", ScoreType, "opponent") getScoreSum() {
    ScoreType own, opponent;

    // タイルポイント
    foreach (i; 0 .. fieldState.height) {
      foreach (j; 0 .. fieldState.width) {
        immutable Color c = fieldState.getColor(i, j);
        immutable ScoreType score = field.getScore(i, j);
        if (c == Color.own) {
          own += score;
        } else if (c == Color.opponent) {
          opponent += score;
        }
      }
    }

    // 領域ポイント
    auto countAreaPoint = (Color c) {
      import std.array;

      immutable int[] dy = [0, 1, 0, -1];
      immutable int[] dx = [1, 0, -1, 0];
      auto visited = new bool[][](fieldState.height, fieldState.width);
      ScoreType ret;

      foreach (i; 0 .. fieldState.height) {
        foreach (j; 0 .. fieldState.width) {
          // すでに調べたやつはskip
          if (visited[i][j])
            continue;

          // 自分のマス以外のマスを調べたいので，自分のマスはskip
          if (c == Color.own && fieldState.getColor(i, j) == Color.own)
            continue;
          if (c == Color.opponent && fieldState.getColor(i, j) == Color.opponent)
            continue;

          Tuple!(int, "y", int, "x")[] stack;
          stack ~= tuple!("y", "x")(cast(int)i, cast(int)j);
          visited[i][j] = true;

          ScoreType sum;
          bool outSide;
          while (!stack.empty) {
            immutable int y = stack.back.y, x = stack.back.x;
            stack.popBack();
            foreach (k; 0 .. 4) {
              int ny = y + dy[k], nx = x + dx[k];
              if (!isInside(ny, nx)) {
                outSide = true;
                continue;
              }
              if (visited[ny][nx])
                continue;
              // 自分のマス以外のマスを調べたいので，自分のマスはskip
              if (c == Color.own && fieldState.getColor(ny, nx) == Color.own)
                continue;
              if (c == Color.opponent && fieldState.getColor(ny, nx) == Color.opponent)
                continue;

              visited[ny][nx] = true;
              stack ~= tuple!("y", "x")(ny, nx);
            }
            import std.math : abs;

            sum += abs(field.getScore(y, x));
          }
          if (!outSide)
            ret += sum;
        }
      }
      return ret;
    };

    own += countAreaPoint(Color.own);
    opponent += countAreaPoint(Color.opponent);

    return tuple!("own", "opponent")(own, opponent);
  }

  string toString() const {
    import std.format : format;
    import std.string : chomp;

    string res;

    res ~= _field.toString() ~ '\n';
    res ~= _fieldState.toString() ~ '\n';

    foreach (const ref e; _own) {
      res ~= e.toString() ~ '\n';
    }

    foreach (const ref e; _opponent) {
      res ~= e.toString() ~ '\n';
    }

    return res.chomp;
  }

}

unittest {
  string s = "2 2\n1 2\n3 4\n0 0\n1 0\n0 1\n1 1";
  auto state = State(s);
  assert(state.toString() == "2 2\n1 2\n3 4\n1 2\n1 2\n0 0\n1 0\n0 1\n1 1");
  state.opponent[0].trans(1);
  assert(state.own[0].y == 0 && state.own[0].x == 0);
}
