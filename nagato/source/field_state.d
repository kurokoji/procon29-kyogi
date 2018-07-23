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

enum FieldStateType
{
    white = 0,
    own,
    opponent
}

struct FieldState
{
    uint _height, _width;
    FieldStateType[][] _states;

    this(uint h, uint w)
    {
        _state = new FieldStateType[][](h, w);
        foreach (i; 0 .. h)
        {
            foreach (j; 0 .. w)
            {
                _states[i][j] = FieldStateType.WHITE;
            }
        }
    }

    FieldStateType getFieldState(uint h, uint w)
    {
        return _states[h][w];
    }

    void changeFieldState(uint h, uint w, FieldStateType state)
    {
        _states[h][w] = state;
    }
}
