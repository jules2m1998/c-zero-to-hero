#include <stdio.h>

int main(void) {
  int arr[5] = {10, 20, 30, 40, 50};
  int *p = arr;

  printf("%d\n", *p);
  printf("%d\n", *(p + 2));
  printf("%d\n", p[3]);
  printf("%d\n", arr[2]);
  printf("%d\n", *(arr + 4));

  p++;
  printf("%d\n", *p);
  printf("%d\n", p[2]);

  return 0;
}
