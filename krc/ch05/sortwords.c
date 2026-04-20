#include <stdio.h>
#include <string.h>

void bubble_sort(char *arr[], int n);
void swap(char **a, char **b);

int main(void) {
  char *jours[] = {"banane", "pomme", "abricot", "cerise", "datte"};
  int n = sizeof(jours) / sizeof(jours[0]);
  bubble_sort(jours, n);
  for (int i = 0; i < n; i++) {
    printf("%s\n", jours[i]);
  }
  return 0;
}

void bubble_sort(char *arr[], int n) {
  for (int i = 0; i < n; i++) {
    int swapped = 0;
    for (int j = 0; j < n - i - 1; j++) {
      if (strcmp(arr[j], arr[j + 1]) > 0) {
        swapped = 1;
        swap(&arr[j], &arr[j + 1]);
      }
    }
    if (swapped == 0) {
      break;
    }
  }
}

void swap(char **a, char **b) {
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}
