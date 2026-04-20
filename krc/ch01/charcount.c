#include <stdio.h>

int main(void) {
  int c;
  int count = 0;
  while ((c = getchar()) != EOF) {
    count++;
  }

  printf("\ntotal char typed = %d\n", count);
  printf("EOF = %d\n", EOF);
  return 0;
}
