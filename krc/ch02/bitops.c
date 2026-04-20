#include <stdio.h>

/* retourne la valeur du bit N de x (0 ou 1) */
int bit_get(unsigned int x, int n);

/* retourne x avec le bit N mis à 1 */
unsigned int bit_set(unsigned int x, int n);

/* retourne x avec le bit N mis à 0 */
unsigned int bit_clear(unsigned int x, int n);

int main(void) {
  unsigned int x = 0xAB; /* 1010 1011 en binaire */
  printf("x         = 0x%X\n", x);
  printf("bit_get(x, 0) = %d\n", bit_get(x, 0)); /* attendu: 1 */
  printf("bit_get(x, 1) = %d\n", bit_get(x, 1)); /* attendu: 1 */
  printf("bit_get(x, 2) = %d\n", bit_get(x, 2)); /* attendu: 0 */
  printf("bit_get(x, 7) = %d\n", bit_get(x, 7)); /* attendu: 1 */
  x = bit_set(x, 2);
  printf("bit_set(x, 2) = 0x%X\n", x); /* attendu: 0xAF */
  x = bit_clear(x, 7);
  printf("bit_clear(x,7)= 0x%X\n", x); /* attendu: 0x2F */

  return 0;
}

int bit_get(unsigned int x, int n) { return (x >> n) & 1; }

unsigned int bit_set(unsigned int x, int n) { return x | (1 << n); }

unsigned int bit_clear(unsigned int x, int n) { return x & ~(1 << n); }
