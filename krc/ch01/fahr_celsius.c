#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void) {
  for (int fahr = LOWER; fahr <= UPPER; fahr += STEP) {
    int celsius = 5 * (fahr - 32) / 9;
    printf("%3d %5d\n", fahr, celsius);
  }
  return 0;
}
