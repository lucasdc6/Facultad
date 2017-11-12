procedure abuela()
{
  int lapices_c = 10;
  int lapices_n = 15;
  int id_niño;

  while(true){
    if(!lapices_c; niño_c[*]? pedido_color(id_niño) -> lapices_c--; niño_c[id_niño]!dar('C'));
    [] (!lapices_n; niño_n[*]? pedido_negro(id_niño) -> lapices_n--; niño_n[id_niño]!dar('N'));
    [] (!lapices_c; niño_a[*]? pedido_color(id_niño) -> lapices_c--; niño_a[id_niño]!dar('C'));
    [] (!lapices_n; niño_a[*]? pedido_negro(id_niño) -> lapices_n--; niño_a[id_niño]!dar('N'));
    [] (niño_c[*]?retrono_color() -> lapices_c++;
    [] (niño_n[*]?retrono_negro() -> lapices_n++;
    [] (niño_a[*]?retrono_color() -> lapices_c++;
    [] (niño_a[*]?retrono_negro() -> lapices_n++;
    }
  }
}

procedure niño_c()[id = 1..N]
{
  char lapiz;
  while(true){
    abuela!pedido_color(id);
    abuela?dar(lapiz);
    delay(10);
    abuela!retorno_color();
  }
}


procedure niño_n()[id = 1..N]
{
  char lapiz;
  while(true){
    abuela!pedido_negro(id);
    abuela?dar(lapiz);
    delay(10);
    abuela!retorno_negro();
  }
}


procedure niño_a()[id = 1..N]
{
  char lapiz;
  while(true){
    lapiz = tipo_lapiz();
    if(lapiz = 'C') {
      abuela!pedido_color(id);
    } else {
      abuela!pedido_negro(id);
    }
    abuela?dar(lapiz);
    delay(10);
    abuela!retorno_color();
  }
}
