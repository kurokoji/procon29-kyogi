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

/// ゲームの盤面を表すノード
struct Node {
  import nagato.state : State;

  Node* parentNode;
  Node*[] childNodes;
  Node*[] untriedNodes;
  State st;
  int winCount;
  int visitCount;
  uint nowTurn;
  Color playerColor;

  this(ref State s, Node* pN, uint nt, Color c) {
    st = s;
    parentNode = pN;
    nowTurn = nt;
    playerColor = c;
  }

  import nagato.color : Color;

  void propagate(bool win) {
    int pt = cast(int)(win);
    for (auto n = &this; n != null; n = n.parentNode) {
      n.update(pt);
    }
  }

  void update(int preWin) {
    winCount += preWin;
    ++visitCount;
  }

  Node*[] makeCandidates() {
    if (childNodes.length == 0 && untriedNodes.length != 0)
      return untriedNodes.dup;

    import nagato.agent, std.range;

    Node*[] ret;

    auto invColor = playerColor == Color.own ? Color.opponent : Color.own;

    foreach (i; 1 .. 9) {
      foreach (j; 1 .. 9) {
        State nextState = st;
        with (nextState) {
          import nagato.color : Color;

          Agent[] ag = playerColor == Color.own ? own : opponent;
          ag[0].trans(i);
          ag[1].trans(j);

          if (!isInside(ag[0].point) || !isInside(ag[1].point))
            continue;

          foreach (ref o, c; lockstep(ag, [i, j])) {
            if (fieldState.getColor(o.y, o.x) == invColor) {
              fieldState.changeColor(o.y, o.x, Color.none);
              o.backTrans(c);
            } else {
              fieldState.changeColor(o.y, o.x, playerColor);
            }
          }
        }
        if (nextState.isValidState()) {
          ret ~= new Node(nextState, &this, nowTurn + 1, invColor);
          untriedNodes ~= ret.back;
        }
      }
    }

    return ret;
  }

  Node* randomTurnNextNodeSelect() {
    import std.random, std.range;

    auto rnd = Xorshift(unpredictableSeed);

    auto invColor = playerColor == Color.own ? Color.opponent : Color.own;

    State nextState;
    do {
      nextState = st;

      auto r = iota(1, 9);
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
        foreach (ref agent, c; lockstep(ag, [i, j])) {
          if (fieldState.getColor(agent.y, agent.x) == invColor) {
            fieldState.changeColor(agent.y, agent.x, Color.none);
            agent.backTrans(c);
          } else {
            fieldState.changeColor(agent.y, agent.x, playerColor);
          }
        }

        ag = opponent;
        foreach (ref agent, c; lockstep(ag, [k, l])) {
          if (fieldState.getColor(agent.y, agent.x) == playerColor) {
            fieldState.changeColor(agent.y, agent.x, Color.none);
            agent.backTrans(c);
          } else {
            fieldState.changeColor(agent.y, agent.x, invColor);
          }
        }
      }
    } while (!nextState.isValidState());

    return new Node(nextState, &this, nowTurn + 2, playerColor);
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

        Agent[] agent = playerColor == Color.own ? own : opponent;
        uint i = r.choice(rnd), j = r.choice(rnd);
        agent[0].trans(i);
        agent[1].trans(j);

        if (!isInside(agent[0].point) || !isInside(agent[1].point))
          continue;

        Agent[] ag = agent;
        foreach (ref a, c; lockstep(ag, [i, j])) {
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
    while (move.nowTurn < maxTurn * 2) {
      move = move.randomNextNodeSelect();
    }

    return move;
  }
}

class PrimitiveMonteCalroTreeSearch {
  import nagato.state;
  import nagato.color : Color;

  Node* rootNode;
  Node*[] childNodes;
  uint playoutN, maxTurn, nowTurn;
  State state;
  Color playerColor;

  this(ref State s, uint tries, uint nowTurn, uint turn, Color c) {
    rootNode = new Node(s, null, nowTurn, c);
    playerColor = c;
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
        res.propagate(judge(res.st) == playerColor);
      }
    }

    import std.algorithm : maxElement, map;

    auto ret = childNodes.maxElement!"a.winCount";
    return ret.st;
  }
}

/// モンテカルロ木探索
class NeoMonteCalroTreeSearch : PrimitiveMonteCalroTreeSearch {
  import nagato.state : State;
  import nagato.color : Color;

  this(ref State s, uint tries, uint nowTurn, uint maxTurn, Color c) {
    super(s, tries, nowTurn, maxTurn, c);
  }

  /// UCB1の値に従ってexpandするノードを決定する
  Node* selectChild(Node* node) {
    import std.algorithm : maxIndex, map;
    import std.math : log, sqrt;

    auto tv = rootNode.visitCount;
    auto cn = rootNode.childNodes;

    // TODO: パラメータの調整が必要
    return cn[cn.map!(x => cast(double)x.winCount / cast(
        double)x.visitCount + sqrt(2.0) * sqrt(log(tv) / cast(double)x.visitCount)).maxIndex];
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
    import std.algorithm : maxElement, map;
    import std.range : iota;
    import core.sync.mutex, core.thread : ThreadGroup;

    debug writefln("Start... %s", childNodes.length);
    debug writefln("Now Turn... %s", nowTurn);

    auto mut = new Mutex;

    // TODO: プレイアウトの高速化
    foreach (i; parallel(playoutN.iota)) {
      Node* node = rootNode;

      // 次の手に関してすべて調べていた場合，有利な手に関して木を成長させる
      while (node.untriedNodes.length == 0 && node.childNodes.length != 0)
        node = selectChild(node);

      if (node.untriedNodes.length != 0)
        node = expandChild(node);

      auto res = node.playout(maxTurn);
      synchronized (mut) {
        res.propagate(judge(res.st) == playerColor);
      }
    }

    debug writeln(rootNode.childNodes.map!"cast(double)a.winCount / cast(double)a.visitCount");
    debug writeln(rootNode.childNodes.map!"cast(double)a.winCount / cast(double)a.visitCount".maxElement);
    // 勝率よりも最もプレイアウト回数が高い手のほうが安定性がある
    return rootNode.childNodes.maxElement!("a.visitCount").st;
    //return rootNode.childNodes.maxElement!("cast(double)a.winCount / cast(double)a.visitCount").st;
  }
}
