#include <stdio.h>

int add(int a, int b) { return a + b; }

int main(void) {
  int x = add(3, 4);
  printf("%d + %d = %d", 3, 4, x);
  return x;
}
