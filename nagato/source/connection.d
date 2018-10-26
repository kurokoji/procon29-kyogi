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

module nagato.connection;

class NagatoSocket {
  import std.socket : Socket;
  import std.socket : getAddress, AddressFamily, SocketType, ProtocolType;
  import std.socket : SocketShutdown;
  import std.string : indexOf;
  import nagato.state : State;
  import std.format : format;

  Socket socket;
  char[] ip;
  ushort port;
  this(string ip, ushort port) {
    this.ip = cast(char[])ip;
    this.port = port;
  }

  void setup() {
    import core.thread;
    Thread.sleep(300.msecs);
    socket = new Socket(AddressFamily.INET, SocketType.STREAM, ProtocolType.TCP);
    auto addresses = getAddress(ip, port);
    socket.connect(addresses[0]);
  }

  string getProblem() {
    long size;
    string ret;
    ubyte[1024] buf;

    do {
      setup();
      ret = "";
      do {
        socket.send("GET problem\n");
        size = socket.receive(buf);
        ret ~= cast(string)buf;
      }
      while (size == 0);
      socket.shutdown(SocketShutdown.BOTH);
      socket.close;
    }
    while (ret.indexOf("NG") != -1);

    string fix;
    for (int i = 0; ret[i] != '\0'; ++i) {
      fix ~= ret[i];
    }

    return fix;
  }

  void postAnswer(ref State s) {
    setup();

    string res;
    foreach (const ref e; s.agentVec[]) {
      res ~= format("%s\n", e);
    }

    res ~= format("%s %s\n", s.nowTurn / 2, s.maxTurn);
    socket.send("POST answer\n");
    socket.send(res);
    socket.shutdown(SocketShutdown.BOTH);
    socket.close;
  }

  string getTurn() {
    long size;
    string ret;
    ubyte[1024] buf;

    do {
      setup();
      ret = "";
      do {
        socket.send("GET turn\n");
        size = socket.receive(buf);
        ret ~= cast(string)buf;
      }
      while (size == 0);
      socket.shutdown(SocketShutdown.BOTH);
      socket.close;
    }
    while (ret.indexOf("NG") != -1);

    string fix;
    for (int i = 0; ret[i] != '\0'; ++i) {
      fix ~= ret[i];
    }
    return fix;
  }

  void postTurn(ref State s) {
    setup();

    string res;
    res ~= format("%s %s\n", s.nowTurn, s.maxTurn);
    socket.send("POST turn\n");
    socket.send(res);
    socket.shutdown(SocketShutdown.BOTH);
    socket.close;
  }

  string getMove() {
    long size;
    string ret;
    ubyte[1024] buf;

    do {
      setup();
      ret = "";
      do {
        socket.send("GET move\n");
        size = socket.receive(buf);
        ret ~= cast(string)buf;
      }
      while (size == 0);
      socket.shutdown(SocketShutdown.BOTH);
      socket.close;
    }
    while (ret.indexOf("NG") != -1);

    string fix;
    for (int i = 0; ret[i] != '\0'; ++i) {
      fix ~= ret[i];
    }
    return fix;
  }
}
