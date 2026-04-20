#include <stdio.h>

int main(void) {
  int fahr = 0;
  while (fahr <= 300) {
    int celcius = 5 / 9 * (fahr - 32);
    printf("%d %d\n", fahr, celcius);
    fahr += 20;
  }
  return 0;
}
