require 'concurrent'

semaphore = Concurrent::Semaphore.new(5)
threads = []
cant = 0
puts 'empezando'

begin
  loop do
    threads << Thread.new do
      semaphore.acquire
      cant += 1
      puts "usando recurso - #{Time.now.to_i} - #{semaphore.available_permits} "
      semaphore.release
    end
  end
rescue ThreadError
  threads.each(&:join)
end

puts "fin #{cant} hilos creados"
