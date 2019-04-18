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

void print_matrix(double *matrix, int N)
{
  for (int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      printf(" %g ", matrix[i*N+j]);
    }
    printf("\n");
  }
}

int main(int argc, char* argv[])
{
  // Check arguments
  if (argc < 2)
  {
    printf("You must specify:\n\t- matrix size\n");
    exit(1);
  }

  #ifdef DEBUG
  int debug = 1;
  if (getenv("DEBUG")) {
    debug = atoi(getenv("DEBUG"));
    printf(ANSI_COLOR_RED "Debug mode - Level %d\n" ANSI_COLOR_RESET, debug);
  }  else {
    printf(ANSI_COLOR_YELLOW "Debug binary\nSet DEBUG environment variable with a level\n" ANSI_COLOR_RESET);
  }
  #endif

  // Initialize variable
  double initial_time;
  int check = 1;
  int N = atoi(argv[1]);;
  double *A; // Matriz A
  double *B; // Matriz B
  double *C; // Matriz C
  
  #ifdef DEBUG
  if (debug > 1) {
    printf("\nInitial variablres:\n\n");
    printf("N = %d\n\n", N);
  }
  #endif

  // Alloc matrix A, B and C
  A = (double*)malloc(sizeof(double)*N*N);
  B = (double*)malloc(sizeof(double)*N*N);
  C = (double*)malloc(sizeof(double)*N*N);

  // Matrix initialization
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      A[i * N + j] = 1; 
      B[i * N + j] = 1;
    }
  }   

  //Start processor time
  initial_time = dwalltime();

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      int aux = 0;
      for(int k = 0; k < N; k++){
        aux += A[i*N+k] * B[k+j*N];
      }
      C[i*N+j] = aux;
    }
  }

  printf("Time %g\n", dwalltime() - initial_time);

  //Verifica el resultado
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      check = check && (C[i*N+j] == N);
    }
  }

  #ifdef DEBUG
  if (debug > 2) {
    printf("\n---------------------------------------------------------------------------------------\n");
    print_matrix(A, N);
    printf("\n---------------------------------------------------------------------------------------\n");
    print_matrix(B, N);
    printf("\n---------------------------------------------------------------------------------------\n");
    print_matrix(C, N);
    printf("\n---------------------------------------------------------------------------------------\n\n");
  }
  #endif

  free(A);
  free(B);
  free(C);
  
  if(!check){
    printf("Multiplication error!\n");
    return 2;
  }

  printf("Everything it's ok!\n");
  return 0;
}