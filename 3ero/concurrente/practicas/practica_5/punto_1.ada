procedure test is
  TASK TYPE auto;
  TASK TYPE camioneta;
  TASK TYPE camion;

  TASK puente IS
    ENTRY auto_pide_puente;
    ENTRY auto_sale;
    ENTRY camioneta_pide_puente;
    ENTRY camioneta_sale;
    ENTRY camion_pide_puente;
    ENTRY camion_sale;
  end puente;

  TASK BODY puente IS
  begin
    SELECT WHEN
    null;
  end puente;
begin
  null;
end test;

