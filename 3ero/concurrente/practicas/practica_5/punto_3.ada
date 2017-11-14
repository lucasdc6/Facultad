procedure buscador is
  TASK TYPE contador is
    ENTRY buscar(numero: IN integer);
  end contador;

  TASK administrador is
    ENTRY resultado_busqueda(numero: IN integer)
  end administrador;

  type contadores is array (1..N) of contador;

  TASK BODY contador is
    array_interno is array(1..C) of integer;
    coincidencias: integer;
    numero: integer;
  begin
  coincidencias := 0;
    accept buscar(numero_buscar) do
      numero := numero_buscar;
    end buscar;

    for i := 1 to C do
      if(array_interno(i) = numero) then
        coincidencias := coincidencias + 1;
      end if;
    end for;
    administrador.resultado_busqueda(coincidencias);
  end contador;

  TASK BODY administrador is
    numero_buscar: integer;
    total: integer;
  begin
    total := 0;
    numero_buscar := random();
    for i := 1 to N do
      contadores(i).buscar(numero_buscar);
    end for;

    for i := 1 to N do
      accept resultado_busqueda(resultado) do
        total := total + resultado;
      end resultado_busqueda;
    end for;
  end administrador;
end buscador;
