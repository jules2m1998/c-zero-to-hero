#include "block.h"
#include "itoa.h"
#include <stdio.h>

int main(void) {
  unsigned int h1 = block_encode(64, 1);
  unsigned int h2 = block_encode(128, 0);

  char s[5] = {0};
  itoa(1234, s);

  printf("h1: size=%zu allocated=%u\n", block_size(h1), block_allocated(h1));
  printf("h2: size=%zu allocated=%u\n", block_size(h2), block_allocated(h2));
  printf("itoa : %s\n", s);

  return 0;
}
