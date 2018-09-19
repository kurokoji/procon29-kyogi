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

module nagato.monte_calro.d;

class MonteClaroTreeSearch {
  import nagato.state;

  struct Node {
    this() {
    }

    this(State s, Node* pN) {
      st = s;
      parentNode = pN;
      makeCandidates();
    }

    Node* parentNode;
    State st;

    int winCount;
    int visitCount;

    void propagate(Color c) {
      int pt = cast(int)(c == Color.own);
      for (auto n = this; n != null; n = n.parentNode)
        update(pt);
    }

    void update(int preWin) {
      winCount += preWin;
      ++visitCount;
    }

    Node*[] makeCandidates() {
      Node*[] ret;
      foreach (i; 0 .. 9) {
        foreach (j; 0 .. 9) {
          foreach (k; 0 .. 9) {
            foreach (l; 0 .. 9) {
              auto nextState = st;
              with (nextState) {
                own[0].trans(i);
                own[1].trans(j);
                opponent[0].trans(k);
                opponent[1].trans(l);
              }

              if (nextState.isValidState())
                ret ~= new Node(nextState, this);
            }
          }
        }
      }
      return ret;
    }

    import nagato.color;

    Node* playout() {
      auto nextNode = makeCandidates();

      import std.random;

      auto rnd = Xorshift(unpredictableSeed);

      Node* move;
      auto moves = makeCandidates();
      foreach (i; 0 .. maxTurn) {
        move = moves.choice(rnd);
        moves = move.makeCandidates();
      }

      return move;
    }
  }

  Node* rootNode;
  Node*[] childNodes;
  uint playoutN, maxTurn;
  State st;

  this(State s, uint tries, uint turn) {
    rootNode = new Node(s, null);
    childNodes = rootNode.makeCandidates();
    st = s;
    this.tries = tries;
    maxTurn = turn;
  }

  State solve() {
    foreach (e; childNodes) {
      foreach (i; 0 .. playoutN) {
        auto res = e.playout();
        res.propagate(res.st);
      }
    }

    import std.algorithm : maxElement;

    return childNodes.maxElement!("a.winCount").st;
  }
}
