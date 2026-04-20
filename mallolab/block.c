#include <stddef.h> /* pour size_t */

/*
 * Un bloc mémoire est précédé d'un en-tête (header) qui encode
 * sa taille ET son statut (alloué/libre) dans un seul unsigned int.
 * Le bit 0 = statut : 1 = alloué, 0 = libre.
 * Les bits restants = taille (multiple de 8, donc bits 0-2 toujours libres).
 */

/* Encoder taille et statut dans un header */
unsigned int block_encode(size_t size, unsigned int allocated) {
  return size | allocated;
}

/* Extraire la taille d'un header */
size_t block_size(unsigned int header) { return header & ~1; }

/* Extraire le statut d'un header (1 = alloué, 0 = libre) */
unsigned int block_allocated(unsigned int header) { return header & 1; }
