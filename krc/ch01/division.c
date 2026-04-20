#include <stdio.h>

int main(void) {
  printf("5/9               =%d\n", 5 / 9);
  printf("5.0/9             =%f\n", 5.0 / 9);
  printf("5/9.0             =%f\n", 5 / 9.0);
  printf("(double)5/9       =%f\n", (double)5 / 9);
  printf("5/9*9             =%d\n", 5 / 9 * 9);
  printf("5*9/9             =%d\n", 5 * 9 / 9);
  return 0;
}
