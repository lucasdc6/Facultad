#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
  #ifdef DEBUG
  int debug = 0;
  if (getenv("DEBUG")) {
    debug = atoi(getenv("DEBUG"));
    printf(ANSI_COLOR_RED "Debug mode - Level %d\n" ANSI_COLOR_RESET, debug);
  }
  #endif

  // Check for thread_number
  if (argc < 3) {
    printf("You must specify:\n\n\t- verctor size\n\t- number to search\n");
    return 1;
  }

  // Initialize variable
  long long int vector_size = atoll(argv[1]);
  int *numbers = (int*) malloc(sizeof(int) * vector_size);
  long long int ocurrences = 0;
  int number = atoi(argv[2]);

  #ifdef DEBUG
  if (debug > 0) {
    printf("\nInitial variablres:\n\n");
    printf("vector_size = %lld\nnumber = %d\n\n", vector_size, number);
  }
  #endif

  for (long long int i = 0; i < vector_size; i++) {
    numbers[i] = rand()%10;
  }

  int initial_time = dwalltime();

  for (int i = 0; i < vector_size; i++) {
    if (numbers[i] == number) {
      ocurrences++;
    }
  }

  printf("Time %g\n", dwalltime() - initial_time);
  printf("Total ocurrences = %lld\n", ocurrences);

  free(numbers);
  return 0;
}