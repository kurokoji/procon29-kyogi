require 'socket'

Port = 20000

def main()
    problem_str = ''
    server = TCPServer.open(Port)

    loop do
        client = server.accept
        puts 'start'
        while res = client.gets
            puts res
            res.chomp!
        end
        client.close
    end
end

if __FILE__ == $0
    main()
end
