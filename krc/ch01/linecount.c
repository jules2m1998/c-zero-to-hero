
#include <stdio.h>

int main(void) {
  int line_count = 0;
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      line_count++;
    }
  }
  printf("\nlines : %d\n", line_count);
  return 0;
}
