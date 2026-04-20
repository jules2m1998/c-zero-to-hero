#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))

#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')
#define TO_LOWER(c) ((c) + ('a' - 'A'))

int main(void) {
  printf("MAX(10, 11) = %d\n", MAX(10, 11));
  printf("MIN(10, 11) = %d\n", MIN(10, 11));
  printf("ABS(-10) = %d\n", ABS(-10));
  printf("IS_UPPER('A') = %d\n", IS_UPPER('A'));
  printf("IS_LOWER('a') = %d\n", IS_LOWER('a'));
  printf("TO_LOWER('A') = %c\n", TO_LOWER('A'));

  return 0;
}
