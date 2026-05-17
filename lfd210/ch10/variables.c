int G_x = 10;
int G_y = 12;
int G_z;

int f(int x, int *y) {
  const int c = 5;
  int t = x;
  t += *y;
  t += c;
  t += G_x;
  return t;
}

int main() {
  int x = 1;
  int y = 2;
  int r = f(x, &y);
  G_y = r;
  G_y = G_x + 5;
  return r;
}
