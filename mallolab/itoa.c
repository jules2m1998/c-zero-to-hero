#include <stdio.h>

void itoa(int n, char s[]) {
  int start = 0;
  int i = 0;
  if (n < 0) {
    s[i++] = '-';
    n = -n;
    start = 1;
  }
  int next = n;
  do {
    s[i++] = (next % 10) + '0';
    next = next / 10;
  } while (next != 0);

  int j = start;
  int mirror = i - 1;

  s[i] = '\0';

  while (mirror > j) {
    char temp = s[j];
    s[j++] = s[mirror];
    s[mirror--] = temp;
  }
}
