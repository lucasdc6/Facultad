require 'concurrent'

sem = Concurrent::Semaphore.new(6)
alta = Concurrent::Semaphore.new(4)
baja = Concurrent::Semaphore.new(5)
l = 500
k = 500
threads = []

l.times do
  threads << Thread.new do
    sleep
    alta.acquire
    sem.acquire
    puts "alta usando BD #{sem.available_permits} "
    sem.release
    alta.release
  end
end

k.times do
  threads << Thread.new do
    sleep
    baja.acquire
    sem.acquire
    puts "baja usando BD #{sem.available_permits} "
    sem.release
    baja.release
  end
end

threads.shuffle!
threads.each(&:run)
