#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *f = fopen("_input.txt", "r");
  if (f == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  int c;
  while ((c = fgetc(f)) != EOF) {
    putchar(c);
  }
  fclose(f);
  return 0;
}
