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

class PrimitiveMonteCalroTreeSearch {
  import nagato.state;

  struct Node {
    Node* parentNode;
    State st;
    int winCount;
    int visitCount;
    uint nowTurn;
    Color playerColor;

    this(State s, Node* pN, uint nt = 0, Color c = Color.own) {
      st = s;
      parentNode = pN;
      nowTurn = nt;
      playerColor = c;
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
      import nagato.agent, std.range;
      Node*[] ret;

      foreach (i; 1 .. 9) {
        foreach (j; 1 .. 9) {
          State nextState = st;
          with (nextState) {
            import nagato.color : Color;
            own[0].trans(i);
            own[1].trans(j);

            if (!isInside(own[0].point) || !isInside(own[1].point)) continue;

            Agent[] ag = own;
            foreach (ref o, c; zip(ag, [i, j])) {
              if (fieldState.getColor(o.y, o.x) == Color.opponent) {
                fieldState.changeColor(o.y, o.x, Color.none);
                o.backTrans(c);
              } else {
                fieldState.changeColor(o.y, o.x, Color.own);
              }
            }
          }
          if (nextState.isValidState()) {
            ret ~= new Node(nextState, &this, nowTurn + 1, Color.opponent);
          }
        }
      }

      return ret;
    }

    Node* randomTurnSelect() {
      import std.random, std.range;

      auto rnd = Xorshift(unpredictableSeed);

      State nextState;
      do {
        nextState = st;

        auto r = iota(0, 9);
        with (nextState) {
          import nagato.color : Color;
          import nagato.agent;

          uint i = r.choice(rnd), j = r.choice(rnd), k = r.choice(rnd), l = r.choice(rnd);
          own[0].trans(i);
          own[1].trans(j);
          opponent[0].trans(k);
          opponent[1].trans(l);

          if (!isInside(own[0].point) || !isInside(own[1].point)
              || !isInside(opponent[0].point) || !isInside(opponent[1].point))
            continue;

          Agent[] ag = own;
          foreach (ref agent, c; zip(ag, [i, j])) {
            if (fieldState.getColor(agent.y, agent.x) == Color.opponent) {
              fieldState.changeColor(agent.y, agent.x, Color.none);
              agent.backTrans(c);
            } else {
              fieldState.changeColor(agent.y, agent.x, Color.own);
            }
          }

          ag = opponent;
          foreach (ref agent, c; zip(ag, [k, l])) {
            if (fieldState.getColor(agent.y, agent.x) == Color.own) {
              fieldState.changeColor(agent.y, agent.x, Color.none);
              agent.backTrans(c);
            } else {
              fieldState.changeColor(agent.y, agent.x, Color.opponent);
            }
          }
        }
      } while (!nextState.isValidState());

      return new Node(nextState, &this, nowTurn + 1);
    }

    Node* randomSelect() {
      import std.random, std.range;

      auto rnd = Xorshift(unpredictableSeed);

      State nextState;
      auto invColor = playerColor == Color.own ? Color.opponent : Color.own;
      auto r = iota(1, 9);
      do {
        nextState = st;
        with (nextState) {
          import nagato.color : Color;
          import nagato.agent;
          auto agent = playerColor == Color.own ? own : opponent;
          uint i = r.choice(rnd), j = r.choice(rnd);
          agent[0].trans(i);
          agent[1].trans(j);

          if (!isInside(agent[0].point) || !isInside(agent[1].point)) continue;

          Agent[] ag = agent;
          foreach (ref a, c; zip(ag, [i, j])) {
            if (fieldState.getColor(a.y, a.x) == invColor) {
              fieldState.changeColor(a.y, a.x, Color.none);
              a.backTrans(c);
            } else {
              fieldState.changeColor(a.y, a.x, playerColor);
            }
          }
        }
      } while (!nextState.isValidState());

      return new Node(nextState, &this, nowTurn + 1, invColor);
    }

    Node* playout(uint maxTurn) {
      import std.random;

      Node* move = randomSelect();
      foreach (i; 0 .. maxTurn - 1) {
        move = move.randomTurnSelect();
      }

      return move;
    }
  }

  Node* rootNode;
  Node*[] childNodes;
  uint playoutN, maxTurn, nowTurn;
  State state;

  this(State s, uint tries, uint nowTurn, uint turn) {
    rootNode = new Node(s, null, nowTurn);
    childNodes = rootNode.makeCandidates();
    state = s;
    this.playoutN = tries;
    this.nowTurn = nowTurn;
    maxTurn = turn;
  }

  State solve() {
    import nagato.util : judge;
    import std.parallelism : parallel;
    import std.array;
    import std.range : iota;
    import std.stdio : writefln, writeln;

    debug writefln("Start %s", childNodes.length);
    debug writefln("Now Turn: %s", nowTurn);
    foreach (index, e; childNodes) {
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
