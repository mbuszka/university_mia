#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

typedef long ul_t;
typedef long long ull_t;

long long inv(long long a, long long b) {
  long long  u, w, x, z, q;

  u = 1; w = a;
  x = 0; z = b;
  while (w) {
    if (w < z) {
      q = u; u = x; x = q;
      q = w; w = z; z = q;
    }
    q = w / z;
    u -= q * x;
    w -= q * z;
  }

  if (x < 0) x += b;
  return x;
}

ull_t binomial(ull_t n, ull_t k, ull_t p) {
  k = k < n - k ? k : n - k;
  ull_t c = 1;
  for (ull_t i = 0; i < k; i ++) {
    c = (c * (n - i)) % p;
  }

  long long d = 1;
  for (long long i = 1; i <= k; i ++) {
    d = (d * i) % p;
  }
  d = inv(d, p);
  c = (c * d) % p;
  return c;
}

int main () {
  ull_t t, n, k, p;
  scanf("%llu", &t);
  for (ull_t i = 0; i < t; i ++) {
    scanf("%llu %llu %llu", &n, &k, &p);
    if (n == 0 || n == 1 || n == k) {
      printf("1\n");
      continue;
    }
    printf("%llu\n", binomial(n, k, p));
  }
  return 0;
}