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

module nagato.container.zobrist_hash;

class ZobristHash
{
    private
    {
        ulong[][][][] _hash;
        uint _height, _width;
    }

    this()
    {
    }

    this(uint height, uint width, uint fieldStateLength, uint agentStateLength)
    {
        import std.random;

        _hash = new ulong[][][][](height, width, fieldStateLength, agentStateLength);
        auto rnd = Mt19937_64(unpredictableSeed);

        foreach (i; 0 .. height)
        {
            foreach (j; 0 .. width)
            {
                foreach (k; 0 .. fieldStateLength)
                {
                    foreach (l; 0 .. agentStateLength)
                    {
                        _hash[i][j][k][l] = rnd.front;
                        rnd.popFront;
                    }
                }
            }
        }
    }

    import nagato.state;

    ulong update(ref State st)
    {
        ulong ret;
        foreach (i; 0 .. _height)
        {
            foreach (j; 0 .. _width)
            {
                ret ^= _hash[i][j][st.fieldState[i, j]][st.agentExists(i, j)];
            }
        }

        return ret;
    }
}
