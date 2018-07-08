sem mutex = 1;

process pasajero[i = 1..N]
{
  P(mutex);
  //uso del detector
  V(mutex);
}
