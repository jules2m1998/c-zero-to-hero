#include <stdio.h>

int main(void) {
  unsigned int header;

  unsigned int size = 128;
  unsigned int allocated = 0;
  header = size | allocated;

  unsigned int extracted_size = header & ~(1 << 0);
  unsigned int is_allocated = header & (1 << 0);

  printf("header    = 0x%X\n", header);
  printf("size      = %u\n", extracted_size);
  printf("allocated = %u\n", is_allocated);
  return 0;
}
