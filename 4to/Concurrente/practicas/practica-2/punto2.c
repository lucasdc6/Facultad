sem resources_mutex = 5;
sem mutex = 1;

int resources[5] = ([5], 1);

process so_process(i = 1..N)
{
  P(resources_mutex);
  P(mutex);
  int rec = desencolar_recurso();
  V(mutex);
  //usar recurso
  encolar_recurso(rec);
  V(resources_mutex);
}
