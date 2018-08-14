sem switch_server = 1;
int time = 0;

queue adn_buffer;

procedure client[int id = 1..N]() {
  while (true) {
    int adn = get_adn();
    P(mutex);
    enqueue(adn_buffer, adn);
    V(mutex);
    P(wait[id]);
  }
}

procedure server[1..2]() {
  while (true) {
    P(switch_server);
    P(mutex);
    int adn = dequeue(adn_buffer);
    V(mutex);
    adn = trabajar(adn.data);
    P(mutex);
    response[adn.client] = adn;
    V(mutex);
    V(wait[adn.client]);
    time = get_work_time();
    if (time >= 5) {
      V(switch_server);
    }
  }
}
