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
            if res == 'POST problem'
                problem_str = ''
                while buf = client.gets
                    problem_str << buf
                end
            end

            if res == 'GET problem'
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
