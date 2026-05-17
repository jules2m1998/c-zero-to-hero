extern int function_asm(int);

int main() {
  int s = 8;
  int t = 4;
  int a = 2;
  a = function_asm(a);
  a = a + t;
  a = a + s;
  return a;
}
