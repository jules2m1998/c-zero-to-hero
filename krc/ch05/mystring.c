#include <stdio.h>

int my_strlen(const char *s);
void my_strcpy(char *dst, const char *src);

int main(void) {
  char *s = "hello";
  char dest[6] = {0};

  int lenght = my_strlen("hello");
  my_strcpy(dest, s);

  printf("lenght = %d\n", lenght);
  printf("dest = %s\n", dest);
  return 0;
}

int my_strlen(const char *s) {
  const char *p = s;
  while (*p) {
    p++;
  }
  return p - s;
}

void my_strcpy(char *dst, const char *src) {
  while ((*(dst++) = *(src++)))
    ;
}
