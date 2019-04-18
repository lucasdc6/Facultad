#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

double dwalltime()
{
	double sec;
	struct timeval tv;

	gettimeofday(&tv,NULL);
	sec = tv.tv_sec + tv.tv_usec/1000000.0;
	return sec;
}

void printf_vector(int *vector, int vector_size)
{
  printf("[");
  for (int i = 0; i < vector_size; i++) {
    printf(" %d", vector[i]);
    if (i != vector_size-1) {
      printf(",");
    }
  }
  printf(" ]\n");
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("You must specify a verctor size\n");
    return 1;
  }

  #ifdef DEBUG
  int debug = 0;
  if (getenv("DEBUG")) {
    debug = atoi(getenv("DEBUG"));
    printf(ANSI_COLOR_RED "Debug mode - Level %d\n" ANSI_COLOR_RESET, debug);
  } else {
    printf(ANSI_COLOR_YELLOW "Debug binary\nSet DEBUG environment variable with a level\n" ANSI_COLOR_RESET);
  }
  #endif

  int initial_time, vector_size = atoi(argv[1]);
  int *vector;

  #ifdef DEBUG
  if (debug > 0) {
    printf("\nInitial variablres:\n\n");
    printf("vector_size = %d\n\n", vector_size);
  }
  #endif

  vector = (int*) malloc(sizeof(int) * vector_size);

  for (int i = 0; i < vector_size; i++) {
    vector[i] = rand()%10;
  }

  #ifdef DEBUG
  if (debug > 1) {
    printf("Vector values: \n");
    printf_vector(vector, vector_size);
    printf("\n\n");
  }
  #endif

  initial_time = dwalltime();



  printf("Time %g\n", dwalltime() - initial_time);

  return 0;
}