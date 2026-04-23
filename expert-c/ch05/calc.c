#include <stdio.h>
#include <stdlib.h>

int add(int, int);
int sub(int, int);
int mul(int, int);
int divide(int, int);

int main(void) {
  int (*ops[4])(int, int) = {add, sub, mul, divide};
  int a;
  int b;
  char op;
  if (scanf("%d %c %d", &a, &op, &b) != 3) {
    printf("Formating error, expected : a op b\n");
    return EXIT_FAILURE;
  }
  int result;
  switch (op) {
  case '+':
    result = ops[0](a, b);
    break;
  case '-':
    result = ops[1](a, b);
    break;
  case '*':
    result = ops[2](a, b);
    break;
  case '/':
  case 'x':
    result = ops[3](a, b);
    break;
  default:
    printf("Invalid operation %c is not supported as a valid operation\n", op);
    return EXIT_FAILURE;
  }
  printf("%d %c %d = %d\n", a, op, b, result);
  return 0;
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divide(int a, int b) {
  if (b == 0) {
    printf("ERROR : Division by zero\n");
    exit(EXIT_FAILURE);
  }
  return a / b;
}
