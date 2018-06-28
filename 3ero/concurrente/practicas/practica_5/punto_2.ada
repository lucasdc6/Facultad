Procedure banco is
  TASK TYPE cliente;

  TASK empleado is
    ENTRY esperando_atencion;
  end empleado;

  TASK BODY empleado is
  begin
    loop
      accept esperando_atencion do
        null;
        -- atender
      end esperando_atencion;
    end loop;
  end empleado;

  TASK BODY cliente is
  begin
    select empleado.esperando_atencion;
    or delay 60 * 10;
    end select;
    null;
    -- chao
  end cliente;
begin
  null;
end banco;
