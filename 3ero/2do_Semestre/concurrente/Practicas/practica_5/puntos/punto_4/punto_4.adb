with Ada.Text_IO; use Ada.Text_IO;
procedure punto_4 is
  a: CONSTANT integer := 4;
  b: CONSTANT integer := 5;
  c: CONSTANT integer := 2;

  TASK db IS
    ENTRY read;
    ENTRY write;
  end db;

  TASK TYPE one IS
  end one;

  TASK TYPE two IS
  end two;

  TASK TYPE three IS
  end three;

  TASK BODY db is
    cant_readers: integer;
    catn_writers: integer;
  begin
    SELECT
    WHEN(cant_readers = 0 and then cant_writers = 0)=>
      ACCEPT read do
        null;
      end read;

      ACCEPT write do
        null;
      end write;
  end SELECT;
end db;

TASK BODY one is
begin
  null;
end one;

TASK BODY two is
begin
  null;
end two;

TASK BODY three is
begin
  null;
end three;

type one_array is array(1..a) of one;
type two_array is array(1..b) of two;
type three_array is array(1..c) of three;

begin
  null;
end punto_4;
