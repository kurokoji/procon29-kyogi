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

module nagato.field_state;

// Fieldが塗られているかどうかなどの状態を示す
struct FieldState {
  import nagato.color : Color;

  private {
    uint _height, _width;
    Color[][] _states;
  }

  this(uint h, uint w) {
    _states = new Color[][](h, w);
    _height = h;
    _width = w;
    foreach (i; 0 .. h) {
      foreach (j; 0 .. w) {
        _states[i][j] = Color.none;
      }
    }
  }

  Color getColor(uint h, uint w) const {
    return _states[h][w];
  }

  void changeColor(uint h, uint w, Color state) {
    _states[h][w] = state;
  }

  ref inout(Color) opIndex(uint i, uint j) inout {
    return _states[i][j];
  }

  @property {
    uint height() const {
      return _height;
    }

    uint width() const {
      return _width;
    }
  }

  string toString() const {
    string ret;
    import std.format : format;
    import std.string : chomp;

    foreach (i; 0 .. _height) {
      foreach (j; 0 .. _width) {
        ret ~= format("%s%s", cast(int) _states[i][j], j == _width - 1 ? '\n' : ' ');
      }
    }

    return ret.chomp;
  }
}

unittest {
  import nagato.color : Color;

  auto st = FieldState(2, 2);
  st.changeColor(1, 1, Color.own);
  assert(st[1, 1] == Color.own);
  assert(st.toString() == "0 0\n0 1");
}
