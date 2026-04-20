#include "block.h"
#include <stdio.h>
#include <unistd.h>

#define GET_COMBINED(addr) (block_size(*(addr)) + (2 * sizeof(unsigned int)))

unsigned int *header_start;
unsigned int *heap_end;

static void *heap_grow(size_t size) {
  void *ptr = sbrk(size);

  if (ptr == (void *)-1) {
    return NULL;
  }
  return ptr;
}
static unsigned int *get_next(unsigned int *header) {
  return (unsigned int *)((char *)header + 2 * sizeof(unsigned int) +
                          block_size(*header));
}

static unsigned int *get_prev(unsigned int *header) {
  unsigned int *prev_footer = header - 1;

  return (unsigned int *)((char *)prev_footer - sizeof(unsigned int) -
                          block_size(*prev_footer));
}

void mem_init(size_t heap_size) {
  header_start = (unsigned int *)heap_grow(heap_size);
  *header_start = block_encode(heap_size - 2 * sizeof(unsigned int), 0);
  heap_end = get_next(header_start);
  *(heap_end - 1) = *header_start;
}

void mem_dump(void) {
  unsigned int *current = header_start;
  int i = 0;

  while (current != heap_end) {
    size_t size = block_size(*current);
    int is_free = block_allocated(*current);
    current = get_next(current);
    printf("Block %d's size = %zu is free = %s\n", ++i, size,
           !is_free ? "yes" : "no");
  }
}

void *mem_malloc(size_t size) {
  unsigned int *current = header_start;
  while (current != heap_end) {
    int is_free = block_allocated(*current);
    size_t availlable = block_size(*current);

    if (!is_free && (availlable >= size)) {
      *current = block_encode(size, 1);
      unsigned int *end = get_next(current) - 1;
      *end = *current;

      if (size + 2 * sizeof(unsigned int) <= availlable) {
        unsigned int *next = get_next(current);
        *next = block_encode(availlable - size - 2 * sizeof(unsigned int), 0);

        unsigned int *end = get_next(next) - 1;
        *end = *next;
      }
      return current + 1;
    }
    current = get_next(current);
  }
  return NULL;
}

void mem_free(void *ptr) {
  unsigned int *header = (unsigned int *)((char *)ptr - sizeof(unsigned int));
  size_t size = block_size(*header);

  unsigned int *prev_end = header - 1;

  unsigned int *next = get_next(header);

  if (header != header_start) {
    int prev_availlable = block_allocated(*prev_end);
    if (!prev_availlable) {
      unsigned int *prev = get_prev(header);
      size += GET_COMBINED(prev);
      header = prev;
    }
  }

  if (next != heap_end) {

    int next_allocated = block_allocated(*next);
    if (!next_allocated) {
      size += GET_COMBINED(next);
    }
  }
  *header = block_encode(size, 0);
  unsigned int *end = get_next(header) - 1;
  *end = *header;
}
