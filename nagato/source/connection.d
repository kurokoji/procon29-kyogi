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
    socket = new Socket(AddressFamily.INET, SocketType.STREAM, ProtocolType.TCP);
    auto addresses = getAddress(ip, port);
    socket.connect(addresses[0]);
  }

  string getProblem() {
    setup();
    long size;
    ubyte[1024] buf;
    do {
      socket.send("GET problem\n");
      size = socket.receive(buf);
    } while (size == 0);

    socket.shutdown(SocketShutdown.BOTH);
    socket.close;
    auto ret = cast(string)buf;

    return ret;
  }

  void postAnswer(ref State s) {
    setup();

    string res;
    foreach (const ref e; s.agentVec[]) {
      res ~= format("%s\n", e);
    }

    auto wl = s.getScoreSum;
    res ~= format("%s %s", wl.own, wl.opponent);
    socket.send("POST answer\n");
    socket.send(res);
    socket.shutdown(SocketShutdown.BOTH);
    socket.close;
  }
}
