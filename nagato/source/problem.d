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

module nagato.problem;

struct Problem
{
    import nagato.field;
    import nagato.agent;

    alias ScoreType = int;
    Field!ScoreType _field;
    Agent[2] own, opponent;

    this(const ref string s)
    {
        import std.conv : to;
        import std.algorithm : map;
        import std.string : split;
        import nep.scanner;

        auto sc = new Scanner(s);
        int h, w;
        sc.scan(h, w);
        ScoreType[][] ar = new ScoreType[][](h, w);
        foreach (i; 0 .. h)
        {
            ar[i] = sc.nextArray!ScoreType(w);
        }
        _field = Field!ScoreType(h, w, ar);

        foreach (ref e; own)
        {
            int y, x;
            sc.scan(y, x);
            e = Agent(y, x);
        }

        foreach (ref e; opponent)
        {
            int y, x;
            sc.scan(y, x);
            e = Agent(y, x);
        }
    }
}
