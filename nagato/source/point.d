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

struct Point(T = uint)
{
    private
    {
        T _y, _x;
    }

    this(T y, T x)
    {
        _y = y;
        _x = x;
    }

    string toString() const
    {
        import std.format : format;

        return format("%s %s", _y, _x);
    }

    @property
    {
        ref T y()
        {
            return _y;
        }

        ref T x()
        {
            return _x;
        }
    }
}
