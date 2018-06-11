procedure buscador is
  TASK TYPE contador is
    ENTRY buscar(numero: IN integer);
  end contador;

  TASK administrador is
    ENTRY resultado_busqueda(numero: IN integer);
  end administrador;

  type contadores is array (1..N) of contador;

  TASK BODY contador is
    type array_interno is array(1..C) of integer;
    coincidencias: integer;
    numero: integer;
  begin
  coincidencias := 0;
    accept buscar(numero_buscar) do
      numero := numero_buscar;
    end buscar;

    for i in Integer range 1..C loop
      if(array_interno(i) = numero) then
        coincidencias := coincidencias + 1;
      end if;
    end loop;
    administrador.resultado_busqueda(coincidencias);
  end contador;

  TASK BODY administrador is
    numero_buscar: integer;
    total: integer;
  begin
    total := 0;
    numero_buscar := random;
    for i in Integer range 1..N loop
      contadores(i).buscar(numero_buscar);
    end loop;

    for i in Integer range 1..N loop
      accept resultado_busqueda(resultado) do
        total := total + resultado;
      end resultado_busqueda;
    end loop;
  end administrador;
begin
  null;
end buscador;
