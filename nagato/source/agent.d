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

enum AgentTeam
{
    none = 0,
    own,
    opponent
}

struct Agent
{
    import nagato.point;

    private
    {
        Point!int _point;
        AgentTeam _agentTeam;
    }

    this(int y, int x, AgentTeam t)
    {
        _point = Point!int(y, x);
        _agentTeam = t;
    }

    this(const ref Point!int point, AgentTeam t)
    {
        _point = point;
        _agentTeam = t;
    }

    @property
    {
        Point!int point()
        {
            return _point;
        }

        int y()
        {
            return _point.y;
        }

        int x()
        {
            return _point.x;
        }

        AgentTeam agentTeam()
        {
            return _agentTeam;
        }
    }

    void trans(int y, int x)
    {
        _point += Point!int(y, x);
    }

    void trans(const ref Point!int trans)
    {
        _point += trans;
    }

    string toString() const
    {
        import std.format : format;

        return format("%s %s", _point.y, _point.x);
    }
}

unittest
{
    auto a = Agent(1, 2, AgentTeam.own);
    assert(a.y == 1 && a.x == 2 && a.agentTeam == AgentTeam.own);
    assert(a.toString() == "1 2");
}
