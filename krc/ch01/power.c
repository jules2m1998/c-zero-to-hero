#include <stdio.h>

int power(int base, int n);

int main(void) {
  printf("power(2, 10) = %d\n", power(2, 10));
  printf("power(3, 4) = %d\n", power(3, 4));
  printf("power(-2, 5) = %d\n", power(-2, 5));
  return 0;
}

int power(int base, int n) {
  int result = 1;
  for (int i = 0; i < n; i++) {
    result *= base;
  }
  return result;
}
