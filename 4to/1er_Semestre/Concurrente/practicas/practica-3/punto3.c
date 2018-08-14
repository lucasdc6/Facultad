Monitor Bank() {
  cond queue[P];
  queue clients;
  bool attended[P] = ([P] false);

  procedure wait(int id) {
    push(clients, id);
    wait(queue[id]);
  }

  procedure attend() {
    if (!empty(clients)) {
      int id = pop(clients);
      attended[id] = true;
      signal(queue[id]);
    }
  }

  procedure go(id) {
    if (!attended[id]) {
      remove(clients, id);
      signal(queue[id]);
    }
  }

}

procedure Employee() {
  while(true) {
    Bank.attend();
  }
}

Monitor TimerMonitor[id = 1..P]() {
  cond pos;
  bool s = false;

  procedure V(){
    s = true;
    signal(pos);
  }

  procedure P() {
    if (!s) {
      wait(pos);
    }
    s = false;
  }
}

procedure Person[int id = 1..P] {
  TimerMonitor.V();
  Bank.wait(id);
}

procedure Timer[int id = 1..P] {
  TimerMonitor.P();
  sleep(15);
  Bank.go(id);
}
