#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

#ifdef DEBUG
int debug = 0;
#endif

int *numbers;
int min = INT_MAX;
int max = INT_MIN;
long long int block_size;
pthread_mutex_t lock;

void * calculate_min_max(void *arg) {
  int id = *(int*) arg;
  long long int start = id * block_size;
  long long int limit = (1+id) * block_size;
  int local_min = INT_MAX;
  int local_max = INT_MIN;

  #ifdef DEBUG
  if (debug > 0) {
    printf("\nIn thread %d\n", id);
    printf("start = %lld\nlimit = %lld\ninitial local_min = %d\ninitial local_max = %d\n\n", start, limit, local_min, local_max);
  }
  #endif

  //printf("Start: %lld - end: %lld\n", id*block_size, (1+id)*block_size);
  for (long long int i = start; i < limit; i++) {
    if (numbers[i] < local_min) {
      local_min = numbers[i];
    }

    if (numbers[i] > local_max) {
      local_max = numbers[i];
    }
  }

  printf("Local min = %d\nlocal_max = %d\n", local_min, local_max);
  pthread_mutex_lock(&lock);
  min = min < local_min ? min : local_min;
  max = max > local_max ? max : local_max;
  pthread_mutex_unlock(&lock);
  pthread_exit(NULL);
  return 0;
}

double dwalltime()
{
	double sec;
	struct timeval tv;

	gettimeofday(&tv,NULL);
	sec = tv.tv_sec + tv.tv_usec/1000000.0;
	return sec;
}

int main(int argc, char* argv[])
{
  // Check for thread_number
  if (argc < 3) {
    printf("You must specify\n\n\t- thread number\n\t- verctor size\n");
    return 1;
  }

  #ifdef DEBUG
  if (getenv("DEBUG")) {
    debug = atoi(getenv("DEBUG"));
    printf(ANSI_COLOR_RED "Debug mode - Level %d\n" ANSI_COLOR_RESET, debug);
  }
  #endif

  // Set thread_number and initialize threads ids array
  int thread_number = atoi(argv[1]);
  int ids[thread_number];
  long long int vector_size = atoll(argv[2]);

  block_size = vector_size / thread_number;

  #ifdef DEBUG
  if (debug > 1) {
    printf("\nInitial variablres:\n\n");
    printf("thread_number = %d\nvector_size = %lld\nblock_size = %lld\n\n", thread_number, vector_size, block_size);
  }
  #endif

  // Alloc memory
  numbers = (int*) malloc(sizeof(int) * vector_size);

  for (long long int i = 0; i < vector_size; i++) {
    numbers[i] = rand();
  }

  // Declare threads and mutex
  pthread_t threads[thread_number];
  pthread_mutex_init(&lock, NULL);

  // Start processor time
  int initial_time = dwalltime();

  // Run threads
  for (int i = 0; i < thread_number; i++) {
    ids[i] = i;
    pthread_create(&threads[i], NULL, calculate_min_max, &ids[i]);
  }

  // Wait for all threads
  for (int i = 0; i < thread_number; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("Time %g\n", dwalltime() - initial_time);
  printf("Min = %d\nMax = %d\n", min, max);

  free(numbers);
  return 0;
}