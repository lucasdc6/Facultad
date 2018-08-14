Procedure punto_3 is
  TASK TYPE contador;
  TASK administrador IS
    ENTRY buscar_numero(numero: IN integer);
  end administrador;

  type t_contadores is array(1..10) of contador;
  contadores: t_contadores;

  TASK BODY contador IS
  begin
    null;
  END contador;

  TASK BODY administrador IS
  begin
    ACCEPT buscar_numero(numero: integer) do
      DELAY 1.0;
    end;
  end administrador;
begin
  contadores(1).buscar_numero(1);
end punto_3;
