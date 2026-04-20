

#include <stdio.h>
int main(void) {
  unsigned int flags = 0;
  flags |= (1 << 0);
  flags |= (1 << 3);
  printf("flags = 0x%X\n", flags);

  if (flags & (1 << 2)) {
    printf("bit 2:on\n");
  } else {
    printf("bit 2:off\n");
  }

  if (flags & (1 << 3)) {
    printf("bit 3:on\n");
  } else {
    printf("bit 3:off\n");
  }

  flags &= ~(1 << 0);
  printf("flags = 0x%X\n", flags);

  return 0;
}
