#include <stdio.h>
int
add(int a, int b) {
  return a + b;
}
int
minus(int a, int b) {
  return a - b;
}
int
main() {
  int a = 34;
  int b = 23;
  printf("%d + %d is %d\n", a, b, add(a, b));
  printf("%d - %d is %d\n", a, b, minus(a, b));
  return 0;
}
