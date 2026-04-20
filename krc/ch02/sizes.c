#include <limits.h>
#include <stdio.h>

int main(void) {
  printf("sizeof(char)           = %zu octets\n", sizeof(char));
  printf("sizeof(short)          = %zu octets\n", sizeof(short));
  printf("sizeof(int)            = %zu octets\n", sizeof(int));
  printf("sizeof(long)           = %zu octets\n", sizeof(long));
  printf("sizeof(long long)      = %zu octets\n", sizeof(long long));
  printf("sizeof(unsigned)       = %zu octets\n", sizeof(unsigned));
  printf("sizeof(float)          = %zu octets\n", sizeof(float));
  printf("sizeof(double)         = %zu octets\n", sizeof(double));
  printf("sizeof(char *)         = %zu octets\n", sizeof(char *));

  printf("INT_MIN = %d\n", INT_MIN);
  printf("IN_MAX = %d\n", INT_MAX);
  printf("UINT_MAX = %u\n", UINT_MAX);
  return 0;
}
