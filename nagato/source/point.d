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

module nagato.point;

struct Point(T) {
  private {
    T _y, _x;
  }

  this(T _y, T _x) {
    this._y = _y;
    this._x = _x;
  }

  string toString() const {
    import std.format : format;

    return format("%s %s", _y, _x);
  }

  // 2項間の演算子を定義
  Point!T opBinary(string op)(Point!T rhs) {
    return Point!T(mixin("_y" ~ op ~ "rhs.y"), mixin("_x" ~ op ~ "rhs.x"));
  }

  ref Point!T opOpAssign(string op)(Point!T rhs) {
    mixin("_y" ~ op ~ "=" ~ "rhs.y;");
    mixin("_x" ~ op ~ "=" ~ "rhs.x;");

    return this;
  }

  @property {
    ref inout(T) y() inout {
      return _y;
    }

    ref inout(T) x() inout {
      return _x;
    }
  }
}

unittest {
  auto p = Point!int(1, 2);
  assert(p.y == 1 && p.x == 2);

  p += Point!int(1, 1);
  assert(p.y == 2 && p.x == 3);
}
