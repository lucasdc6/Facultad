#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
  int id, thread_number = 0;

  if (argc == 2) {
    thread_number = atoi(argv[1]);
  }


  #pragma omp parallel num_threads(thread_number) private(id)
  {
    id = omp_get_thread_num();

    printf("Hello from %d\n", id);
    if (id == 0) {
      thread_number = omp_get_num_threads();
      printf("Número de hilos = %d\n", thread_number);
    }
  }
  return 0;
}
