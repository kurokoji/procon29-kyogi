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

struct Point(T)
{
    private
    {
        T _y, _x;
    }

    this(T _y, T _x)
    {
        this._y = _y;
        this._x = _x;
    }

    string toString() const
    {
        import std.format : format;

        return format("%s %s", _y, _x);
    }

    // 2項間の演算子を定義
    Point!T opBinary(string op)(Point!T rhs)
    {
        return Point!T(mixin("_y" ~ op ~ "rhs.y"), mixin("_x" ~ op ~ "rhs.x"));
    }

    ref Point!T opOpAssign(string op)(Point!T rhs)
    {
        mixin("_y" ~ op ~ "=" ~ "rhs.y;");
        mixin("_x" ~ op ~ "=" ~ "rhs.x;");

        return this;
    }

    @property
    {
        T y() const
        {
            return _y;
        }

        T x() const
        {
            return _x;
        }
    }
}
