
#include <stdio.h>

void printd(int value);

int main(void) {
  printd(1234);
  putchar('\n');
  printd(-567);
  putchar('\n');
  printd(0);
  putchar('\n');
  return 0;
}

void printd(int value) {
  if (value == 0) {
    putchar('0');
    return;
  }
  if (value < 0) {
    putchar('-');
    value = -value;
  }
  int last_digit = value % 10;
  int next = value / 10;
  if (next != 0) {
    printd(next);
  }
  putchar(last_digit + '0');
}
