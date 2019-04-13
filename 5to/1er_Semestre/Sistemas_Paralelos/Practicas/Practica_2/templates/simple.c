#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * test(void *arg) {
  int id = *(int*) arg;

  printf("Hello from %d\n", id);
  return 0;
}

int main(int argc, char* argv[])
{
  // Check for thread_number
  if (argc < 2) {
    printf("You must specify a number\n");
    return 1;
  }

  // Set thread_number and initialize threads ids array
  int thread_number = atoi(argv[1]);
  int ids[thread_number];

  // Declare threads config
  pthread_attr_t attr;
  pthread_t threads[thread_number];
  pthread_attr_init(&attr);

  // Run threads
  for (int i = 0; i < thread_number; i++) {
    ids[i] = i;
    pthread_create(&threads[i], &attr, test, &ids[i]);
  }

  // Wait for all threads
  for (int i = 0; i < thread_number; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}