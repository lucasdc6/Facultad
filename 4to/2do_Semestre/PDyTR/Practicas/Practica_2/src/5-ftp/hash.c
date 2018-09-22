#include "hash.h"

int hash(char *str)
{
  int hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash%16;
}