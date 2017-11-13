sem start = 0;
sem elegidos = 0;
sem entrega[10] = ([10] 0);
int cant = 0;
int group[10] = ([10] 0);
queue groups;
int group_cant = 0;
int pos = 0;

Process alumno[i = 1..50]
{
  int group_id = elegir();
  cant++;
  if(cant == 50){
    V(elegidos);
  }
  P(start);
  //Hacer tarea
  group[group_id]++;
  if(group[group_id] == 5){
    push(groups, group_id);
    groups_cant++;
    V(entrega[group_id]);
    group[group_id] = 0;
  }
    P(entrega[group_id]);
    printf("Me saque %d\nChau!\n", group[group_id]);
}

Process maestra
{
  P(elegidos);
  V(start);
  while(groups_cant != 10) {
    int group_id = pop(groups);
    P(entrega[group_id]);
    group[group_id] = pos++;
    for(int i = 1; i < 5; i++){
      V(entrega[group_id])
    }
  }
}
