Procedure punto_1 IS

  TASK TYPE auto;
  TASK TYPE camioneta;
  TASK TYPE camion;

  TASK puente IS
    ENTRY pasar_auto;
    ENTRY salir_auto;
    ENTRY pasar_camioneta;
    ENTRY salir_camioneta;
    ENTRY pasar_camion;
    ENTRY salir_camion;
  END puente;

  TASK BODY puente IS
    cant_autos: integer;
    cant_camionetas: integer;
    cant_camiones: integer;
  BEGIN
    cant_autos := 0;
    cant_camionetas := 0;
    cant_camiones := 0;
    LOOP
      SELECT WHEN(cant_autos < 3 && cant_camionetas = 0 && cant_camiones = 0) => ACCEPT pasar_auto; cant_autos := cant_autos + 1; END pasar_auto;
      OR WHEN(cant_autos = 0 && cant_camionetas < 2 && cant_camiones = 0) => ACCEPT pasar_camioneta; cant_camionetas :=  cant_camionetas + 1; END pasar_camioneta;
      OR WHEN(cant_autos = 0 && cant_camionetas = 0 && cant_camiones = 0) => ACCEPT pasar_camion; cant_camiones := cant_camiones + 1; END pasar_camion;
      OR ACCEPT salir_auto; cant_autos := cant_autos - 1; END salir_auto;
      OR ACCEPT salir_camioneta; cant_camionetas := cant_camionetas - 1; END salir_camioneta;
      OR ACCEPT salir_camion; cant_camiones := cant_camiones - 1; END salir_camion;
    END LOOP;
  END puente;

  TASK BODY auto IS
    BEGIN
      puente.pasar_auto;
      -- pasar auto
      puente.salir_auto;
    END
  END auto;

  TASK BODY camioneta IS
    BEGIN
      puente.pasar_camioneta;
      -- pasar camioneta
      puente.salir_camioneta;
    END
  END camioneta;

  TASK BODY camion IS
    BEGIN
      puente.pasar_camion;
      -- pasar camion
      puente.salir_camion;
    END
  END camion;

END punto_1;
