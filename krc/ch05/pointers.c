#include <stdio.h>

int main(void) {
  int x = 42;
  int *p = &x;

  printf("x = %d\n", x);
  printf("&x = %p\n", (void *)&x);
  printf("p = %p\n", (void *)p);
  printf("*p = %d\n", *p);

  *p = 99;
  printf("apres *p = 99 :\n");
  printf("x = %d\n", x);
  printf("*p = %d\n", *p);

  return 0;
}
