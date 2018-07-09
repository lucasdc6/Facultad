buffer buffer_marcos;
sem c_mutex = 1;
int cant_marcos = 0;

buffer buffer_vidrios;
int cant_vidrios = 0;

sem mutex_macros = 1;
sem mutex_vidrios = 1;
sem mutex_armar = 1;


procedure carpintero[1..4]() {
  while(true) {
    P(c_mutex);
    if (cant_marcos < 30) {
      cant_marcos++;
      V(c_mutex);
      // Hacer marco
      P(mutex_macros);
      depositar(buffer_marcos);
      V(mutex_macros);
    }
  }
}
procedure vidriero() {
  while(true) {
    if (cant_vidrios < 50) {
      cant_vidrios++;
      // Hacer vidrio
      P(mutex_vidrios);
      depositar(buffer_vidrios);
      V(mutex_vidrios);
    }
  }
}
procedure armador[1..2]() {
  while(true) {
    P(mutex_armar);
    P(mutex_macros);
    sacar(buffer_marcos);
    V(mutex_marcos);
    P(mutex_vidrios);
    sacar(buffer_vidrios);
    V(mutex_vidrios);
    V(mutex_armar);
    //armar ventana
  }
}
