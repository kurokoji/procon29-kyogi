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

enum SquareColor
{
    white = 0,
    own,
    opponent
}

// Fieldが塗られているかどうかなどの状態を示す
struct FieldState
{
    private
    {
        uint _height, _width;
        SquareColor[][] _states;
    }

    this(uint h, uint w)
    {
        _states = new SquareColor[][](h, w);
        _height = h;
        _width = w;
        foreach (i; 0 .. h)
        {
            foreach (j; 0 .. w)
            {
                _states[i][j] = SquareColor.white;
            }
        }
    }

    SquareColor getSquareColor(uint h, uint w) const
    {
        return _states[h][w];
    }

    void changeSquareColor(uint h, uint w, SquareColor state)
    {
        _states[h][w] = state;
    }

    ref inout(SquareColor) opIndex(uint i, uint j) inout
    {
        return _states[i][j];
    }

    @property
    {
        uint height() const
        {
            return _height;
        }

        uint width() const
        {
            return _width;
        }
    }

    string toString() const
    {
        string ret;
        import std.format : format;
        import std.string : chomp;

        foreach (i; 0 .. _height)
        {
            foreach (j; 0 .. _width)
            {
                ret ~= format("%s%s", cast(int)_states[i][j], j == _width - 1 ? '\n' : ' ');
            }
        }

        return ret.chomp;
    }
}

unittest
{
    auto st = FieldState(2, 2);
    st.changeSquareColor(1, 1, SquareColor.own);
    assert(st[1, 1] == SquareColor.own);
    assert(st.toString() == "0 0\n0 1");
}
