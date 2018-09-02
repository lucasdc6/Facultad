#include <stdlib.h>
int main()
{
  char *buffer = NULL;
  /* No se puede usar 
     la variable buffer */
  buffer = (char*)malloc(256);
  /* Ya se puede usar
     la variable buffer */
  return 0;
}
