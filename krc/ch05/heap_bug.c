#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  /* Allouer un tableau de 5 int sur la heap */
  int *arr = (int *)malloc(5 * sizeof(int));
  if (arr == NULL) {
    fprintf(stderr, "malloc failed\n");
    return 1;
  }

  /* Remplir et afficher */
  for (int i = 0; i < 5; i++) {
    arr[i] = (i + 1) * 10;
  }
  for (int i = 0; i < 5; i++) {
    printf("arr[%d] = %d\n", i, arr[i]);
  }
  free(arr);
  free(arr);

  return 0;
}
