#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#define NUM_THREADS 2

pthread_mutex_t mutex;

void *passenger(void *threadid) {
  long tid;
  tid = (long) threadid;
  pthread_mutex_lock(&mutex);
  sleep(1);
  printf("Passenger #%ld analized!\n", tid);
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  pthread_mutex_init(&mutex, NULL);
  long t;
  int rc;
  for (t = 0; t < NUM_THREADS; t++) {
    printf("In main: creating thread %ld\n", t);
    rc = pthread_create(threads + t, NULL, passenger, (void *) t);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  /* wait for all threads to complete */
  for (t = 0; t < NUM_THREADS; t++) {
    pthread_join(threads[t], NULL);
  }
  pthread_exit(NULL);
  pthread_mutex_destroy(&mutex);
  return 0;
}
