require 'socket'
require './procon29_protocol.rb'
require 'logger'

# ポート
Port = 20000

def main()
  include Procon29
  # 問題データ文字列
  problem_str = ''
  # 答えのデータ文字列
  answer_str = ''
  # move状況の文字列
  move_str = ''

  # TCPサーバ
  server = TCPServer.open(Port)

  # Loggerの設定
  logger = Logger.new(STDOUT)
  logger.info('Program Start...')

  loop do
    # 接続待ち
    client = server.accept

    # 文字列取得
    while res = client.gets
      logger.info('Protocol >> ' + res)

      # 問題のPOST要求(mikuru -> haruhi)
      if res.chomp == Protocol::POST::Problem
        problem_str = ''
        while buf = client.gets
          problem_str << buf
        end
        # 問題データの表示
        logger.info('Problem Data >> ' + problem_str)
      end

      # 問題のGET要求(haruhi -> nagato, kyon)
      if res.chomp == Protocol::GET::Problem
        if problem_str != ''
          client.puts(problem_str)
        else
          client.puts('NG')
        end
      end

      # 答えのPOST要求(nagato -> haruhi)
      if res.chomp == Protocol::POST::Answer
        answer_str = ''
        while buf = client.gets
          answer_str << buf
        end
        # 答えデータの表示
        logger.info('Answer Data >> ' + answer_str)
      end

      # 答えのGET要求(haruhi -> kyon)
      if res.chomp == Protocol::GET::Answer
        if answer_str != ''
          client.puts(answer_str)
          answer_str = ''
        else
          client.puts('NG')
        end
      end

      # moveのPOST要求(kyon -> haruhi)
      if res.chomp == Protocol::POST::Move
        move_str = ''
        while buf = client.gets
          move_str << buf
        end
      end

      # moveのGET要求(haruhi -> nagato)
      if res.chomp == Protocol::GET::Move
        if move_str != ''
          client.puts(move_str)
          move_str = ''
        else
          client.puts('NG')
        end
      end
    end

    # 接続終了
    client.close
  end
end

if __FILE__ == $0
  main()
end
