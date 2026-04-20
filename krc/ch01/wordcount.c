#include <stdio.h>

#define IN 1
#define OUT 0

int main(void) {
  int c;
  int word_count = 0;
  int in_word = OUT;
  while ((c = getchar()) != EOF) {
    if (c != ' ' && c != '\t' && c != '\n') {
      if (in_word == OUT) {
        word_count++;
      }
      in_word = IN;
    } else {
      in_word = OUT;
    }
  }

  printf("\nwords: %d\n", word_count);
  return 0;
}
