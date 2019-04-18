#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

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
  if (argc < 2) {
    printf("You must specify:\n\n\t- verctor size\n");
    return 1;
  }

  #ifdef DEBUG
  int debug = 0;
  if (getenv("DEBUG")) {
    debug = atoi(getenv("DEBUG"));
    printf(ANSI_COLOR_RED "Debug mode - Level %d\n" ANSI_COLOR_RESET, debug);
  }
  #endif

  // Set thread_number and initialize threads ids array
  long long int vector_size = atoll(argv[1]);
  int *numbers;
  int min = INT_MAX;
  int max = INT_MIN;

  #ifdef DEBUG
  if (debug > 1) {
    printf("\nInitial variablres:\n\n");
    printf("vector_size = %lld\nmin = %d\nmax = %d\n\n", vector_size, min, max);
  }
  #endif

  // Alloc memory
  numbers = (int*) malloc(sizeof(int) * vector_size);

  // Initialize Array
  for (long long int i = 0; i < vector_size; i++) {
    numbers[i] = rand();
  }

  // Start time
  int initial_time = dwalltime();

  for (int i = 0; i < vector_size; i++) {
    if (numbers[i] < min) {
      min = numbers[i];
    }

    if (numbers[i] > max) {
      max = numbers[i];
    }
  }

  printf("Time %g\n", dwalltime() - initial_time);
  printf("Min = %d\nMax = %d\n", min, max);

  free(numbers);
  return 0;
}