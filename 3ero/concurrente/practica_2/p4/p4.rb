require 'concurrent'

ALUMNOS = (ARGV[0] || 40).to_i

tareas = ALUMNOS.times.collect { Concurrent::Semaphore.new(1) }
mutex = ALUMNOS.times.collect { Concurrent::Semaphore.new(0) }
correcciones = Array.new(ALUMNOS, false)
entregas = []
cant = ALUMNOS

ALUMNOS.times do | i |
  Thread.new do
    while !correcciones[i]
      tareas[i].acquire # Funcion P del 'lenguaje' de concurrente
      sleep 1 # Se hace tarea
      puts "entregar tarea alumno #{i} "
      entregas.push i
      tareas[i].release # Funcion V del 'lenguaje' de concurrente
      mutex[i].acquire
    end
    puts "alumno #{i}: chau!"
  end
end


maestra = Thread.new do
  while cant != 0
    if !entregas.empty?
      entregas.pop.tap do |id|
        tareas[id].acquire
        [true, false].sample.tap do |correccion| # Se corrige la tarea al azar
          correcciones[id] = correccion
          cant -= 1 if correccion
          puts "correccion tarea #{id} = #{correccion} - faltan #{cant} "
          tareas[id].release
          mutex[id].release
        end
      end
    end
  end
end

maestra.join # Se deja el hilo como el principal
