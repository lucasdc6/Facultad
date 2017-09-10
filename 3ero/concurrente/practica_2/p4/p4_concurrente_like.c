sem tarea[40] = ([40], 1);
sem mutex[40] = ([40], 0);
boolean correcciones[40] = ([40], false);
cola entregas;
int cant = 40;

Process alumnos[i = 1 to 40]
{
  while(!correcciones[i]){
    P(tareas[i]);
    // Hago tarea
    encolar(entregas, i);
    V(tareas[i]);
    P(mutex[id]);
  }
}

Process maestra
{
  while(cant != 0){
    if(!entregas.empty?) {
      int id = desencolar(entregas);
      P(tareas[id]);
      if(//tarea es correcta){
        cant -= 1;
        correcciones[id] = true;
      }
      V(tarea[id]);
      V(maestra[id]);
    }
  }
}
