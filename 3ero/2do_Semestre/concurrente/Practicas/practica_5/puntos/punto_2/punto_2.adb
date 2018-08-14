with Ada.Text_IO;

Procedure punto_2 is
  TASK cliente;

  TASK empleado IS
    ENTRY llega_cliente;
  END empleado;

  TASK BODY empleado IS
  begin
    LOOP
      ACCEPT llega_cliente do
        Ada.Text_IO.Put_Line("Doit");
      END llega_cliente;
    END LOOP;
  END empleado;

  TASK BODY cliente IS
  BEGIN
    SELECT
    empleado.llega_cliente;
    OR
      DELAY 2.0;
    END SELECT;
  Ada.Text_IO.Put_Line("Chau");
  END cliente;
BEGIN
  null;
END punto_2;
