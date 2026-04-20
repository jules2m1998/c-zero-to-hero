
#include <stdio.h>

int main(void) {
  int tab[5] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++) {
    printf("tab[%d]=%d\n", i, tab[i]);
  }
  printf("sizeof(tab) = %zu\n", sizeof(tab));
  printf("nombre de cases = %zu\n", sizeof(tab) / sizeof(tab[0]));
  return 0;
}
