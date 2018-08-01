require 'socket'
require './procon29_protocol.rb'

Port = 20000

def main()
  include Procon29
  problem_str = ''
  server = TCPServer.open(Port)

  loop do
    client = server.accept
    puts 'start'
    while res = client.gets
      puts res
      res.chomp!
      if res == Protocol::POST::Problem
          problem_str = ''
        while buf = client.gets
          problem_str << buf
        end
      end

      if res == Protocol::GET::Problem
        if problem_str != ''
          client.puts(problem_str)
        else
          client.puts('NG')
        end
      end
    end
    client.close
  end
end

if __FILE__ == $0
  main()
end
