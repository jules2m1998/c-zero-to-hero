#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

void mem_init(size_t heap_size); /* initialise le heap */
void *mem_malloc(size_t size);   /* alloue un bloc */
void mem_free(void *ptr);        /* libère un bloc */
void mem_dump(void);             /* affiche l'état du heap */

#endif /* ifndef ALLOCATOR_H */
