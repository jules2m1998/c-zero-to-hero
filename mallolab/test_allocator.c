#include "allocator.h"
#include <stdio.h>

void mem_free(void *ptr);

int main(void) {
  // int *t = heap_grow(0);
  // int *t1 = heap_grow(4096);
  // int *t2 = heap_grow(0);

  // printf("pointer 1 address : %p\n", (void *)t);
  // printf("pointer 2 address : %p\n", (void *)t1);
  // printf("pointer 3 address : %p\n", (void *)t2);
  // printf("diff   : %ld octets\n", (char *)t2 - (char *)t);

  mem_init(1024);
  void *a = mem_malloc(64);
  void *b = mem_malloc(64);
  mem_free(a);
  mem_free(b);
  mem_dump();
  return 0;
}
