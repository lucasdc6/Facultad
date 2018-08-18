#include <stdlib.h>
int main()
{
  char *buffer = NULL;
  // you cannot use buffer
  buffer = (char*)malloc(256);
  // now you can use buffer
  return 0;
}
