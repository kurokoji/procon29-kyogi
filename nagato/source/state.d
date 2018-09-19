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
    import nagato.field_state;
    import nagato.point;
    import nagato.color : Color;
    import std.typecons : Tuple, tuple;

    alias ScoreType = int;
    private
    {
        Field!ScoreType _field;
        FieldState _fieldState;
        Agent[2] _own, _opponent;
    }

    this(ref in string s)
    {
        import std.conv : to;
        import std.algorithm : map;
        import std.string : split;
        import nep.scanner;

        auto sc = new Scanner(s);
        int h, w;
        sc.scan(h, w);

        _fieldState = FieldState(h, w);

        ScoreType[][] ar = new ScoreType[][](h, w);

        foreach (i; 0 .. h)
        {
            ar[i] = sc.nextArray!ScoreType(w);
        }

        _field = Field!ScoreType(h, w, ar);

        foreach (ref e; _own)
        {
            int y, x;
            sc.scan(y, x);
            e = Agent(y, x, Color.own);
        }

        foreach (ref e; _opponent)
        {
            int y, x;
            sc.scan(y, x);
            e = Agent(y, x, Color.opponent);
        }
    }

    @property
    {
        ref inout(FieldState) fieldState() inout
        {
            return _fieldState;
        }
    }

    /+
        与えられた座標にAgentが存在するか
        存在する場合，そのエージェントの列挙型AgentTeamの値が返る
        存在しない場合，SquareColor.noneが返る
    +/
    AgentTeam agentExists(int ny, int nx) const
    {
        auto point = Point!int(ny, nx);
        foreach (e; _own ~ _opponent)
        {
            if (e.point == point)
            {
                return e.agentTeam;
            }
        }

        return AgentTeam.none;
    }

    /+ ditto +/
    inout(AgentTeam) agentExists(ref in Point!int point) inout
    {
        foreach (e; _own ~ _opponent)
        {
            if (e.point == point)
            {
                return e.agentTeam;
            }
        }

        return AgentTeam.none;
    }

    string toString() const
    {
        import std.format : format;
        import std.string : chomp;

        string res;

        res ~= _field.toString() ~ '\n';

        foreach (const ref e; _own)
        {
            res ~= e.toString() ~ '\n';
        }

        foreach (const ref e; _opponent)
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
    assert(state.toString() == s);
}
