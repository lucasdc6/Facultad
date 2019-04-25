#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

#ifdef DEBUG
int debug = 0;
#endif

double dwalltime()
{
	double sec;
	struct timeval tv;

	gettimeofday(&tv,NULL);
	sec = tv.tv_sec + tv.tv_usec/1000000.0;
	return sec;
}

void merge (int *a, int n, int m) {
  int i, j, k;
  int *x = malloc(n * sizeof (int));
  for (i = 0, j = m, k = 0; k < n; k++) {
    x[k] = j == n      ? a[i++]
          : i == m      ? a[j++]
          : a[j] < a[i] ? a[j++]
          :               a[i++];
  }
  for (i = 0; i < n; i++) {
    a[i] = x[i];
  }
  free(x);
}


void merge_sort (int *a, int n) {
    if (n < 2)
        return;
    int m = n / 2;
    merge_sort(a, m);
    merge_sort(a + m, n - m);
    merge(a, n, m);
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

int check(int *vector, int vector_size) {
  for (int i = 0; i < vector_size; i++) {
    if ((i+1) < vector_size && vector[i] > vector[i+1]) {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("You must specify a verctor size\n");
    return 1;
  }

  #ifdef DEBUG
  if (getenv("DEBUG")) {
    debug = atoi(getenv("DEBUG"));
    printf(ANSI_COLOR_RED "Debug mode - Level %d\n" ANSI_COLOR_RESET, debug);
  } else {
    printf(ANSI_COLOR_YELLOW "Debug binary\nSet DEBUG environment variable with a level\n" ANSI_COLOR_RESET);
  }
  #endif

  int initial_time, vector_size = atoi(argv[1]);

  #ifdef DEBUG
  if (debug > 0) {
    printf("\nInitial variablres:\n\n");
    printf("vector_size = %d\n\n", vector_size);
  }
  #endif

  int* vector = (int*) malloc(sizeof(int) * vector_size);

  for (int i = 0; i < vector_size; i++) {
    vector[i] = rand()%10;
  }

  #ifdef DEBUG
  if (debug > 1) {
    printf("Initial Vector: \n");
    printf_vector(vector, vector_size);
    printf("\n\n");
  }
  #endif

  initial_time = dwalltime();

  merge_sort(vector, vector_size);

  printf("Time %g\n", dwalltime() - initial_time);

  #ifdef DEBUG
  if (debug > 1) {
    printf("Sorted Vector: \n");
    printf_vector(vector, vector_size);
    printf("\n\n");
  }
  #endif

  if (check(vector, vector_size)) {
    printf("OK!\n");
  } else {
    printf("NOPE!\n");
  }

  free(vector);

  return 0;
}