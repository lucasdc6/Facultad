class InvalidValue < StandardError
  def initialize(msg = "Debe ingresar un número")
    super msg
  end
end

# Este script lee una secuencia de no menos de 15 números desde teclado y luego imprime el resultado de la división
# de cada número por su entero inmediato anterior.

# Como primer paso se pide al usuario que indique la cantidad de números que ingresará.
cantidad = 0
puts '¿Cuál es la cantidad de números que ingresará? Debe ser al menos 15'
begin
  cantidad = Integer(gets)
  raise InvalidValue unless cantidad >= 15
rescue ArgumentError => e
  puts "#{e.message}. Ingrese un número"
  retry
rescue InvalidValue => e
  puts e.message
  retry
end

# Luego se almacenan los números
numeros = 1.upto(cantidad).map do
  puts 'Ingrese un número'
  begin
    numero = Integer(gets)
    raise InvalidValue unless numero > 1
    numero
  rescue ArgumentError => e
    puts "#{e.message}. Ingrese un número"
    retry
  rescue InvalidValue => e
    puts "#{e.message}. Ingrese un número mayor a 1"
    retry
  end
end

# Y finalmente se imprime cada número dividido por su número entero inmediato anterior
resultado = numeros.map { |x| x / (x - 1) }
puts 'El resultado es: %s' % resultado.join(', ')
