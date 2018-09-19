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

import nagato.state;

struct ContextState {
    State st;
    ContextState* node;
    this() {
    }

    this(State s) {
        st = s;
    }

    this(State s, ContextState* ptr) {
        st = s;
        node = ptr;
    }
}

interface SolverStrategy {
    static ContextState*[] nextState(const ref State);
}

class AllStrategy : SolverStrategy {
    static ContextState*[] nextState(const ref State st) {
        import nagato.color : Color;

        ContextState*[] ret;

        foreach (i; 0 .. 9)
            foreach (j; 0 .. 9)
                foreach (k; 0 .. 9)
                    foreach (l; 0 .. 9) {
                        auto next = st;
                        with (next) {
                            own[0].trans(i);
                            own[1].trans(j);
                            opponent[0].trans(k);
                            opponent[1].trans(l);

                            if (isValidState()) {
                                ret ~= new ContextState(next, &st);
                            }
                        }
                    }

        return ret;
    }
}

struct BeamSearcher(Strategy) {
    import nagato.state;

    State _state;

    this(ref in State st) {
        _state = cast(State) st;
    }

    State solve(State st, uint beamWidth = 100) {
        import std.algorithm : partialSort;

        State[] beam = Strategy.nextState(st);

    }
}
