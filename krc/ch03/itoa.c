#include <stdio.h>

void itoa(int n, char s[]);

int main(void) {
  char s_1234[5] = {0};
  itoa(1234, s_1234);
  printf("%s\n", s_1234);

  char s_negative_42[4] = {0};
  itoa(-42, s_negative_42);
  printf("%s\n", s_negative_42);
  char s_0[2] = {0};
  itoa(0, s_0);
  printf("%s\n", s_0);
  return 0;
}

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
