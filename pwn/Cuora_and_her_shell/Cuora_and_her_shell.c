#include <stdio.h>


int main(void)
{
  setvbuf(stdout, 0, 2, 0);
  setvbuf(stdin, 0, 2, 0);

  printf("where is my shell?\n");

  char  map[200] = {0};
  
  fread(map, sizeof(char), 200, stdin);

  (*((void (*)())(map)))();

  return 0;
}
