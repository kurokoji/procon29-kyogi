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
        foreach (i; 0 .. h)
        {
            foreach (j; 0 .. w)
            {
                _states[i][j] = SquareColor.white;
            }
        }
    }

    SquareColor getSquareColor(uint h, uint w)
    {
        return _states[h][w];
    }

    void changeSquareColor(uint h, uint w, SquareColor state)
    {
        _states[h][w] = state;
    }
}
