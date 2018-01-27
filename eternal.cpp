#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long ull_t;

int main() {
  ull_t a, b;
  scanf("%llu %llu", &a, &b);
  ull_t k = 1;
  ull_t i = a + 1;
  for (; i <= b && i <= a + 10; i ++) {
    k = (k * i) % 10;
  }
  if (i != b + 1) k = 0;
  printf("%llu\n", k);
  return 0;
}