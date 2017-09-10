require 'concurrent'

tareas = []
40.times { tareas << Concurrent::Semaphore.new(0) }
correcciones = Array.new(40, false)
entregas = []
cant = 40

40.times do | i |
  Thread.new do
    while !correcciones[i]
      sleep 5
      puts "entregar tarea alumno #{i} "
      tareas[i].release
      entregas.push i
    end
  end
end


maestra = Thread.new do
  while cant != 0
    if !entregas.empty?
      [true, false].sample.tap do |correccion|
        entregas.pop.tap do |id|
          correcciones[id] = correccion
          cant -= 1 if correccion
          puts "correccion tarea #{id} = #{correccion} - faltan #{cant} "
        end
      end
    end
  end
end

maestra.join
