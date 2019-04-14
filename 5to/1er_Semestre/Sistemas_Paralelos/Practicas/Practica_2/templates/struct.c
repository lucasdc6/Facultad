#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int start;
  int end;
  int id;
} options;

void * test(void *arg) {
  options *param = (options *) arg;

  printf("Hello from %d - with start: %d and end %d\n", param->id, param->start, param->end);
  return 0;
}

int main(int argc, char* argv[])
{
  // Check for thread_number
  if (argc < 2) {
    printf("You must specify a thread number\n");
    return 1;
  }

  // Set thread_number and initialize threads ids array
  int thread_number = atoi(argv[1]);
  options params[thread_number];

  // Declare threads config
  pthread_attr_t attr;
  pthread_t threads[thread_number];
  pthread_attr_init(&attr);

  // Run threads
  for (int i = 0; i < thread_number; i++) {
    params[i] = (options){
      .start = i*thread_number,
      .end = (1+i)*thread_number,
      .id = i
    };

    pthread_create(&threads[i], &attr, test, &params[i]);
  }

  // Wait for all threads
  for (int i = 0; i < thread_number; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}