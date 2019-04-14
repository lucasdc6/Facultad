#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

#ifdef DEBUG
int debug = 1;
#endif

int N;
int thread_number;
int block_size;
double *A; // Matriz A
double *B; // Matriz B
double *C; // Matriz C

double dwalltime()
{
  double sec;
  struct timeval tv;

  gettimeofday(&tv,NULL);
  sec = tv.tv_sec + tv.tv_usec/1000000.0;
  return sec;
}

void* mult(void* arg)
{
  int id = *((int*)arg);
  int start = id * block_size;
  int limit = (id + 1) * block_size;

  #ifdef DEBUG
  if (debug > 0) {
    printf("\nIn thread %d\n", id);
    printf("start = %d\nlimit = %d\n\n", start, limit);
  }
  #endif

  for(int i = start; i < limit; i++){
    for(int j = 0; j < N; j++){
      int aux = 0;
      for(int k = 0; k < N; k++){
        aux += A[i*N+k] * B[k+j*N];
      }
      C[i*N+j] = aux;
    }
  }
  pthread_exit(0);
  return 0;
}

void print_matrix(double *matrix)
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
  double initial_time;
  int check = 1;

  #ifdef DEBUG
  if (getenv("DEBUG")) {
    debug = atoi(getenv("DEBUG"));
    printf(ANSI_COLOR_RED "Debug mode - Level %d\n" ANSI_COLOR_RESET, debug);
  }
  #endif

  // Check arguments
  if (argc < 3)
  {
    printf("You must specify:\n\t- thread number\n\t- matrix size\n");
    exit(1);
  }


  // Initialize variable
  thread_number = atoi(argv[1]);
  N = atoi(argv[2]);
  block_size = N / thread_number;
  int ids[thread_number];
  
  #ifdef DEBUG
  if (debug > 1) {
    printf("\nInitial variablres:\n\n");
    printf("thread_number = %d\nN = %d\nblock_size = %d\n\n", thread_number, N, block_size);
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

  // Inicializacion de threads
  pthread_t threads[thread_number];

  //Realiza la multiplicacion

  initial_time = dwalltime();

  for(int i = 0; i < thread_number; i++){
    ids[i]= i;
    pthread_create(&threads[i], NULL, mult, &ids[i]);
  }   

  for(int i = 0; i < thread_number; i++){
    pthread_join(threads[i], NULL);
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
    print_matrix(A);
    printf("---------------------------------------------------------------------------------------\n");
    print_matrix(B);
    printf("---------------------------------------------------------------------------------------\n");
    print_matrix(C);
    printf("---------------------------------------------------------------------------------------\n\n");
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