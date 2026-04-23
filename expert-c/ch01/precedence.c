#include <stdio.h>

// int main(void) {
//   int x = 1;
//   if (x & 1 == 1)
//     printf("odd\n");
//   else
//     printf("even\n");
//   return 0;
// }

int main(void) {
  // int i = 0;
  // printf("%d %d %d\n", i++, i++, i++);

  // int x = 10;
  // int y = sizeof(x++);
  // printf("x = %d\n", x);

  // char *a = "hello";
  // char b[] = "hello";

  // a[0] = 'H'; /* ligne A */
  // b[0] = 'H'; /* ligne B */
  // printf("%s\n", b);

  char *a = "hello";
  char *b = "hello";
  printf("%d\n", a == b);
  return 0;
}
