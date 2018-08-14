sem tarea = 0;
queue tareas;
int notas[40] = ([40], 0)
sem alumnos[40] = ([40], 0);

process maestra()
{
  for (int i = 0; i < 40; i++) {
    V(tarea);
  }
  int cant = 40;
  while(cant != 0) {
    P(corregir);
    int id_alumno = desencolar(tareas);
    // corregir tarea
    nota_tarea = corregir();
    notas[id_alumno] = nota_tarea;
    if (nota_tarea) {
      cant--;
    }
  }
}

process alumno[id = 0..39]()
{
  P(tarea);
  recibir_tarea();
  while (!notas[id]) {
    // hacer tarea
    encolar(tarea, id);
    V(corregir);
    P(alumnos[id]);
  }
}
