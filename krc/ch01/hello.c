#include <string.h>
int printf(const char *, ...);

int main(void) {
  printf("hello, world\n");
  printf("La taille de la chaine 'a\\n' est de : %zu\n", sizeof("a\n"));
  printf("La taille de la chaine 'a' est de : %zu\n", sizeof("a"));

  printf("sizeof(\"\\0\") = %zu\n", sizeof("\0"));
  printf("strlen(\"\\0\") = %zu\n", strlen("\0"));

  char bogus[] = "bonjour";
  bogus[3] = '\0';

  printf("sizeof(\"\\0\") = %zu\n", sizeof(bogus));
  printf("strlen(\"\\0\") = %zu\n", strlen(bogus));

  return 42;
}
