1)

sem semaphore = 1;

Process pasajero[i = 1 to N]
{
  P(semaphore);
  // Hacer cosas
  V(semaphore);
}


2)

sem semaphore = 3;

Process pasajero[i = 1 to N]
{
  P(semaphore);
  // Hacer cosas
  V(semaphore);
}
