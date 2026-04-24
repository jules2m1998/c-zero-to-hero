#include <stdio.h>
#include <unistd.h>

int main(void) {
  int x = 42;
  printf("adresse de x : %p\n", (void *)&x);
  return 0;
}
