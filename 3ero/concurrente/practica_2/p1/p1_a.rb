require 'concurrent'

semaphore = Concurrent::Semaphore.new(1)
threads = []

puts 'empezando'

1000.times do
  threads << Thread.new do
    sleep
    semaphore.acquire
    puts 'analizando pasajero'
    semaphore.release
  end
end
threads.each(&:run)

puts 'termino'
