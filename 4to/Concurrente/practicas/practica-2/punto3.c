typedef int sem;

sem mutex = 7;

sem trigo = 5;
sem maiz = 5;

process  camion_trigo[i = 1..T]
{
  P(trigo);
  P(mutex);
  //descargar
  V(mutex);
  V(trigo);
}


process  camion_maiz[i = 1..M]
{
  P(maiz);
  P(mutex);
  // descargar
  V(mutex);
  V(maiz);
}
