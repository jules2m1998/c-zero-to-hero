
#include <stdio.h>

#define ARRAY_SIZE(arr) sizeof((arr)) / sizeof((arr[0]))

void swap(int *a, int *b);
void minmax(int *arr, int n, int *min, int *max);

int main(void) {
  int a = 10;
  int b = 11;

  printf("avant le swap\n");
  printf("a = %d\n", a);
  printf("b = %d\n", b);

  swap(&a, &b);
  printf("apres le swap\n");
  printf("a = %d\n", a);
  printf("b = %d\n", b);

  int arr[8] = {3, 1, 4, 1, 5, 9, 2, 6};
  int n = ARRAY_SIZE(arr);
  int min = 0;
  int max = 0;

  minmax(arr, n, &min, &max);

  printf("min = %d\n", min);
  printf("max = %d\n", max);

  return 0;
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void minmax(int *arr, int n, int *min, int *max) {
  int local_min = arr[0];
  int local_max = arr[0];
  for (int i = 1; i < n; i++) {
    int current = arr[i];
    if (current < local_min) {
      local_min = current;
    }
    if (local_max < current) {
      local_max = current;
    }
  }

  *min = local_min;
  *max = local_max;
}
