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

module nagato.beam_searcher;

{
    static ContextState*[] nextState(const ref State st)
    {
    }
}

struct BeamSearcher(Strategy)
{
    import nagato.state;

    State _state;

    this(ref in State st)
    {
    }
}
