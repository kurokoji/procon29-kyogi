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

struct Node {
  import nagato.state;

  Node* parentNode;
  Node*[] childNodes;
  Node*[] untriedNodes;
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
          untriedNodes ~= ret.back;
        }
      }
    }

    return ret;
  }

  Node* randomTurnNextNodeSelect() {
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

  Node* randomNextNodeSelect() {
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

    Node* move = randomNextNodeSelect();
    while (move.nowTurn < maxTurn) {
      move = move.randomTurnNextNodeSelect();
    }

    return move;
  }
}


class PrimitiveMonteCalroTreeSearch {
  import nagato.state;

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

    debug writefln("Start... %s", childNodes.length);
    debug writefln("Now Turn... %s", nowTurn);
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

class NeoMonteCalroTreeSearch : PrimitiveMonteCalroTreeSearch {
  import nagato.state;

  this(State s, uint tries, uint nowTurn, uint maxTurn) {
    super(s, tries, nowTurn, maxTurn);
  }

  // UCB1の値に従ってexpandするノードを決定する
  Node* selectChild(Node* node) {
    import std.range;
    import std.algorithm : maxIndex, map;
    import std.math : log, sqrt;

    auto tv = rootNode.visitCount;
    auto cn = rootNode.childNodes;
    return cn[cn.map!(x => x.winCount / x.visitCount + sqrt(2.0) * sqrt(log(tv) / x.visitCount)).maxIndex];
  }

  // まだ調べてない子ノードから選択する
  Node* expandChild(Node* node) {
    import std.array;
    if (node.untriedNodes.length == 0)
      node.makeCandidates();

    auto next = node.untriedNodes.back;
    node.untriedNodes.popBack();
    node.childNodes ~= next;
    return next;
  }

  override State solve() {
    import nagato.util : judge;
    import std.parallelism : parallel;
    import std.stdio : writefln, writeln;
    import std.algorithm : maxElement;

    debug writefln("Start... %s", childNodes.length);
    debug writefln("Now Turn... %s", nowTurn);

    foreach (i; 0 .. playoutN) {
      Node* node = rootNode;

      // 次の手に関してすべて調べていた場合，有利な手に関して木を成長させる
      while (node.untriedNodes.length == 0 && node.childNodes.length != 0)
        node = selectChild(node);

      if (node.untriedNodes.length != 0)
        node = expandChild(node);

      auto res = node.playout(maxTurn);
      res.propagate(judge(res.st));
    }

    return rootNode.childNodes.maxElement!("a.winCount / a.visitCount").st;
  }
}
