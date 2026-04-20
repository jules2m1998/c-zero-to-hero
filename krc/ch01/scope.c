#include <stdio.h>

int x = 100;

void foo(void) {
  int x = 200;
  printf("foo: x = %d\n", x);
}

void bar(void) {
  printf("bar: x = %d\n", x);
  x = 300;
}

int main(void) {
  printf("main 1: x = %d\n", x);
  foo();
  printf("main 2: x = %d\n", x);
  bar();
  printf("main 3: x = %d\n", x);
  return 0;
}
