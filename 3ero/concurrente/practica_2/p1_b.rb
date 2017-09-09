require 'concurrent'

semaphore = Concurrent::Semaphore.new(3)
threads = []
cant = 0
puts 'empezando'

begin
  loop do
    threads << Thread.new do
      semaphore.acquire
      cant += 1
      puts "analizando pasajero - #{Time.now.to_i} - #{semaphore.available_permits} "
      semaphore.release
    end
  end
rescue ThreadError
  threads.each(&:join)
end

puts "fin #{cant} hilos creados"
