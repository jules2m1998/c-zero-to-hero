#include <stdio.h>
struct point {
  int x;
  int y;
};

struct rect {
  struct point top_left;
  struct point bottom_right;
};

int rect_area(const struct rect *r);
int rect_contains(const struct rect *r, const struct point *p);

int main(void) {
  struct point p1 = {3, 3};
  struct point p2 = {11, 2};

  struct rect rect = {.bottom_right = {0, 0}, .top_left = {10, 5}};

  printf("rect area = %d\n", rect_area(&rect));
  printf("rect contains p1 : %s\n", rect_contains(&rect, &p1) ? "yes" : "no");
  printf("rect contains p2 : %s\n", rect_contains(&rect, &p2) ? "yes" : "no");
  return 0;
}

int rect_area(const struct rect *r) {
  int width = r->top_left.x - r->bottom_right.x;
  int height = r->top_left.y - r->bottom_right.y;

  return width * height;
}

int rect_contains(const struct rect *r, const struct point *p) {
  return (p->x >= r->bottom_right.x && p->x <= r->top_left.x) &&
         (p->y >= r->bottom_right.y && p->y <= r->top_left.y);
}
