#include <stdio.h>

int main(void) {
  int c;
  int digit_count[10] = {0};
  int white_space_count = 0;
  int other_count = 0;

  while ((c = getchar()) != EOF) {
    if (c >= '0' && c <= '9') {
      int i = c - '0';
      digit_count[i]++;
    } else if (c == ' ' || c == '\t' || c == '\n') {
      white_space_count++;
    } else {
      other_count++;
    }
  }

  printf("\ndigits =");
  for (int i = 0; i < 10; i++) {
    printf(" %d", digit_count[i]);
  }
  printf("\n");

  printf("White space = %d\n", white_space_count);
  printf("other = %d\n", other_count);
  return 0;
}
