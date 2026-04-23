#include <stdio.h>

int main(void) {
  int a[5] = {1, 2, 3, 4, 5};
  int *p = a;

  printf("sizeof(a) = %zu\n", sizeof(a));
  printf("sizeof(p) = %zu\n", sizeof(p));

  printf("%p\n", (void *)a);
  printf("%p\n", (void *)&a);
  printf("%p\n", (void *)(a + 1));
  printf("%p\n", (void *)(&a + 1));
  return 0;
}
