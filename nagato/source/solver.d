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

module nagato.solver;

enum SolverStrategy
{
    random,
    greedy,
    beamSearch
}

struct Solver
{
    import nagato.state;

    State _state;

    this(ref in State st)
    {
        _state = cast(State) st;
    }
}
