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

module nagato.state;

struct State
{
    import nagato.field;
    import nagato.agent;

    alias ScoreType = int;
    private
    {
        Field!ScoreType _field;
        Agent[2] own, opponent;
    }

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

    string toString()
    {
        import std.format : format;
        import std.string : chomp;
        string res;

        res ~= _field.toString() ~ '\n';

        foreach (const ref e; own)
        {
            res ~= e.toString() ~ '\n';
        }

        foreach (const ref e; opponent)
        {
            res ~= e.toString() ~ '\n';
        }

        return res.chomp;
    }
}

unittest
{
    string s = "2 2\n1 2\n3 4\n1 1\n2 1\n1 1\n2 2";
    auto state = State(s);
    import std.stdio : writeln;
    assert(state.toString() == s);
}