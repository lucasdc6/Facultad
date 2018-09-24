#include <stdlib.h>
#include <sys/time.h>
#include "utils.h"

uint64_t hash(char *str)
{
  uint64_t hash = 5381;
  uint64_t c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

double dwalltime()
{
  double sec;
  struct timeval tv;

  gettimeofday(&tv, NULL);
  sec = tv.tv_sec + tv.tv_usec/1000.0;
  return sec;
}