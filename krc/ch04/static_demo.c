#include <stdio.h>

void counter(void) {
  static int count = 0;
  count++;
  printf("count = %d\n", count);
}

int main(void) {
  counter();
  counter();
  counter();
  return 0;
}
