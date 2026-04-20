#include <stdio.h>
#include <string.h>

#define COUNT(s) sizeof((s)) / sizeof((s)[0])

void swap(void **a, void **b);
void bubble_sort(void *arr[], int n, int (*cmp)(const void *, const void *));
int cmp_str(const void *a, const void *b);
int cmp_int(const void *a, const void *b);
void print_str_arr(char **s, int n);
void print_int_arr(int **number, int n);

int main(void) {
  char *strs[] = {"banane", "pomme", "abricot"};
  bubble_sort((void *)strs, COUNT(strs), cmp_str);
  printf("Array sort\n");
  print_str_arr(strs, COUNT(strs));

  int *numbers[] = {&(int){300}, &(int){1}, &(int){20}};
  printf("numbers sort\n");
  bubble_sort((void *)numbers, COUNT(numbers), cmp_int);
  print_int_arr(numbers, COUNT(numbers));
  return 0;
}

void bubble_sort(void *arr[], int n, int (*cmp)(const void *, const void *)) {
  for (int i = 0; i < n; i++) {
    int swapped = 0;
    for (int j = 0; j < n - i - 1; j++) {
      if (cmp(arr[j], arr[j + 1]) > 0) {
        swapped = 1;
        swap(&arr[j], &arr[j + 1]);
      }
    }
    if (swapped == 0) {
      break;
    }
  }
}

void swap(void **a, void **b) {
  void *tmp = *a;
  *a = *b;
  *b = tmp;
}
int cmp_str(const void *a, const void *b) {
  return strcmp((const char *)a, (const char *)b);
}
int cmp_int(const void *a, const void *b) {
  return *(const int *)a - *(const int *)b;
}

void print_str_arr(char **s, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d) %s\n", i, s[i]);
  }
}
void print_int_arr(int **numbers, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d\n", numbers[i][0]);
  }
}
