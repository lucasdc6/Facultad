sem alumnos = 0;
sem empezar = 0;
int tareas[10];

process maestra()
{
  for (int i = 0; i < 49; i++){
    P(alumnos);
  }
  for (i = 0; i < 49; i++) {
    V(empezar);
  }
}

process alumno[id = 0..49]()
{
  int id_tarea = elegir();
  V(alumnos);
  P(empezar);
  // hacer tarea
  
}
