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

  Socket socket;
  this(const char[] ip, ushort port) {
    import std.socket : getAddress, AddressFamily, SocketType, ProtocolType;
    socket = new Socket(AddressFamily.INET, SocketType.STREAM, ProtocolType.TCP);
    auto addresses = getAddress(ip, port);
    socket.connect(addresses[0]);
  }

  string getProblem() {
    import std.socket : SocketShutdown;
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

  void postAnswer() {
    import std.socket : SocketShutdown;

    socket.send("POST answer\n");
    socket.shutdown(SocketShutdown.BOTH);
    socket.close;
  }
}
