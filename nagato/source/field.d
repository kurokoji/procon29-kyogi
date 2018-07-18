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

module nagato.field;

struct Field(T)
{
    import std.array;

    private
    {
        T[][] _field;
        uint _height, _width;
    }

    this(uint height, uint width, T[][] ar)
    {
        _height = height;
        _width = width;
        _field = ar;
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

}


