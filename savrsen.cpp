#include <stdlib.h>
#include <stdio.h>

#define BMAX 1000000
#define abs(_x) _x < 0 ? - _x : _x


long long *sum;

int main () {
  int a, b;
  scanf("%d %d", &a, &b);

  sum = (long long*) calloc(b + 1, sizeof(long long));

  for (long long i = 1; i <= b; i ++) {
    for (long long j = 2; j * i <= b; j ++) {
      sum[j * i] += i;
    }
  }

  long long total = 0;

  for (long long i = a; i <= b; i++) {
    long long t = sum[i] - i;
    total += abs(t);
  }

  printf("%lli\n", total);

  free((void *) sum);
  return 0;
}