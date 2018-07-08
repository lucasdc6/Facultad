cola espera;
int state[P] = ([P] 0);
sem start[P] = ([P] 0);
sem wait[P] = ([P] 0);
sem mutex = 1;

procedure timer[int id = 1..P]() {
  P(start[id]);
  sleep("10m");
  P(mutex);
  delete(espera, id);
  V(mutex);
  V(wait[id]);
}

procedure person[int id = 1..P]() {
  P(mutex);
  enqueue(espera, id);
  V(mutex);
  V(start[id]);
  P(wait[id]);
  if (state[id] == 0) {
    printf("Chau!\n");
    exit(1);
  }
  printf("yo quiero comida!\n");
}

procedure employee() {
  P(mutex);
  int id = dequeue(espera);
  V(mutex);
  printf("Que va a querer?\n");
  V(wait[id]);
  // atiende
}
