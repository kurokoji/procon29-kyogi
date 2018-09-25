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

module nagato.montecalro;

class MonteCalroTreeSearch {
  import nagato.state;

  struct Node {
    Node* parentNode;
    State st;
    int winCount;
    int visitCount;

    this(State s, Node* pN) {
      st = s;
      parentNode = pN;
    }

    import nagato.color : Color;

    void propagate(Color c) {
      int pt = cast(int)(c == Color.own);
      for (auto n = &this; n != null; n = n.parentNode) {
        n.update(pt);
      }
    }

    void update(int preWin) {
      winCount += preWin;
      ++visitCount;
    }

    Node*[] makeCandidates() {
      Node*[] ret;
      foreach (i; 1 .. 9) {
        foreach (j; 1 .. 9) {
          foreach (k; 1 .. 9) {
            foreach (l; 1 .. 9) {
              State nextState = st;
              with (nextState) {
                import nagato.color : Color;

                own[0].trans(i);
                own[1].trans(j);
                opponent[0].trans(k);
                opponent[1].trans(l);

                if (!isInside(own[0].point) || !isInside(own[1].point)
                    || !isInside(opponent[0].point) || !isInside(opponent[1].point))
                  continue;
                if (fieldState.getColor(own[0].y, own[0].x) == Color.opponent) {
                  fieldState.changeColor(own[0].y, own[0].x, Color.none);
                  own[0].backTrans(i);
                } else {
                  fieldState.changeColor(own[0].y, own[0].x, Color.own);
                }

                if (fieldState.getColor(own[1].y, own[1].x) == Color.opponent) {
                  fieldState.changeColor(own[1].y, own[1].x, Color.none);
                  own[1].backTrans(j);
                } else {
                  fieldState.changeColor(own[1].y, own[1].x, Color.own);
                }

                if (fieldState.getColor(opponent[0].y, opponent[0].x) == Color.own) {
                  fieldState.changeColor(opponent[0].y, opponent[0].x, Color.none);
                  opponent[0].backTrans(k);
                } else {
                  fieldState.changeColor(opponent[0].y, opponent[0].x, Color.opponent);
                }

                if (fieldState.getColor(opponent[1].y, opponent[1].x) == Color.own) {
                  fieldState.changeColor(opponent[1].y, opponent[1].x, Color.none);
                  opponent[1].backTrans(l);
                } else {
                  fieldState.changeColor(opponent[1].y, opponent[1].x, Color.opponent);
                }
              }

              if (nextState.isValidState()) {
                ret ~= new Node(nextState, &this);
              }
            }
          }
        }
      }
      return ret;
    }

    Node* randomSelect() {
      import std.random, std.range;

      auto rnd = Xorshift(unpredictableSeed);

      State nextState;
      while (true) {
        nextState = st;

        auto r = iota(0, 9);
        with (nextState) {
          import nagato.color : Color;

          uint i = r.choice(rnd), j = r.choice(rnd), k = r.choice(rnd), l = r.choice(rnd);
          own[0].trans(i);
          own[1].trans(j);
          opponent[0].trans(k);
          opponent[1].trans(l);

          if (!isInside(own[0].point) || !isInside(own[1].point)
              || !isInside(opponent[0].point) || !isInside(opponent[1].point))
            continue;
          if (fieldState.getColor(own[0].y, own[0].x) == Color.opponent) {
            fieldState.changeColor(own[0].y, own[0].x, Color.none);
            own[0].backTrans(i);
          } else {
            fieldState.changeColor(own[0].y, own[0].x, Color.own);
          }

          if (fieldState.getColor(own[1].y, own[1].x) == Color.opponent) {
            fieldState.changeColor(own[1].y, own[1].x, Color.none);
            own[1].backTrans(j);
          } else {
            fieldState.changeColor(own[1].y, own[1].x, Color.own);
          }

          if (fieldState.getColor(opponent[0].y, opponent[0].x) == Color.own) {
            fieldState.changeColor(opponent[0].y, opponent[0].x, Color.none);
            opponent[0].backTrans(k);
          } else {
            fieldState.changeColor(opponent[0].y, opponent[0].x, Color.opponent);
          }

          if (fieldState.getColor(opponent[1].y, opponent[1].x) == Color.own) {
            fieldState.changeColor(opponent[1].y, opponent[1].x, Color.none);
            opponent[1].backTrans(l);
          } else {
            fieldState.changeColor(opponent[1].y, opponent[1].x, Color.opponent);
          }
        }

        if (nextState.isValidState())
          break;
      }

      return new Node(nextState, &this);
    }

    Node* playout(uint maxTurn) {
      import std.random;

      auto rnd = Xorshift(unpredictableSeed);

      Node* move = &this;
      foreach (i; 0 .. maxTurn) {
        move = move.randomSelect();
      }

      return move;
    }
  }

  Node* rootNode;
  Node*[] childNodes;
  uint playoutN, maxTurn;
  State state;

  this(State s, uint tries, uint turn) {
    rootNode = new Node(s, null);
    childNodes = rootNode.makeCandidates();
    state = s;
    this.playoutN = tries;
    maxTurn = turn;
  }

  State solve() {
    import nagato.util : judge;
    import std.parallelism : parallel;
    import std.array;
    import std.range : iota;

    debug writefln("Start %s", childNodes.length);
    foreach (index, e; childNodes) {
      // debug writefln("Child %s...", index);
      auto arr = iota(0, playoutN);
      foreach (i; parallel(arr)) {
        auto res = e.playout(maxTurn);
        res.propagate(judge(res.st));
      }
    }

    import std.algorithm : maxElement, map;

    auto ret = childNodes.maxElement!"a.winCount";
    return ret.st;
  }
}
