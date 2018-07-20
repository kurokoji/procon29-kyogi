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

struct Agent
{
    private
    {
        int _y, _x;
    }

    this(int y, int x)
    {
        _y = y;
        _x = x;
    }

    @property
    {
        int y() const
        {
            return _y;
        }

        int x() const
        {
            return _x;
        }
    }

    string toString() const
    {
        import std.format : format;

        return format("%s %s", _y, _x);
    }
}

unittest
{
    auto a = Agent(1, 2);
    assert(a.y == 1 && a.x == 2);
    assert(a.toString() == "1 2");
}