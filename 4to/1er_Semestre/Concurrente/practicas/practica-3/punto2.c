Monitor Computer {
  queue persons;
  cond turn[1..P];
  bool free;

  procedure request(int id, int prio) {
    if (!free) {
      encolar_prioridad(persons, id, prio); // Encolar en la cola, el id con prioridad prio
      wait(turn[id]);
    }
    free = false;
  }

  procedure relese() {
    if (empty(persons)) {
      free = true;
    } else {
      int id = desencolar(persons);
      signal(turn[id]);
    }
  }
}

procedure person[int id = 1..P]() {
  while (true) {
    int prio = get_priority();
    Computer.request(id, prio);
    // Trabajar con computadora
    Computer.relese();
  }
}
