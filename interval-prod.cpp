#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NMAX 0x40000

#define left_child(_n) (_n * 2)
#define right_child(_n) (_n * 2 + 1)
#define sgn(_x) (_x == 0 ? 0 : (_x < 0 ? -1 : 1))
#define show(_x) (_x < 0 ? "-" : (_x > 0 ? "+" : "0"))


typedef unsigned long long ul_t;
typedef char node_t;
ul_t interval_last;
ul_t interval_size;
ul_t singleton_begin;

void set_size(ul_t n) {
  ul_t s = 1;
  while (s < n) s *= 2;
  interval_last = s - 1;
  interval_size = interval_last * 2 + 1;
  singleton_begin = interval_last;
}

node_t *tree = (node_t *) malloc(NMAX * sizeof(ul_t));

char query(ul_t a, ul_t b) {
  ul_t va = singleton_begin + a;
  ul_t vb = singleton_begin + b;
  char res = tree[va];
  if (vb != va) res *= tree[vb];
  do {
    ul_t apred = (va - 1) / 2;
    ul_t bpred = (vb - 1) / 2;
    if (apred == bpred) break;
    if (va % 2 == 1) res *= tree[va + 1];
    if (vb % 2 == 0) res *= tree[vb - 1];
    va = apred; vb = bpred;
  } while (1);
  return res;
}

void set(ul_t x, char v) {
  ul_t vx = singleton_begin + x;
  tree[vx] = v;
  while (vx != 0) {
    vx = (vx - 1) / 2;
    tree[vx] = tree[2 * vx + 1] * tree[2 * vx + 2];
  }
}

void show_state(ul_t n) {
  for (ul_t i = 0; i < n; i++) {
    char p = query(i, i);
    printf("%s", show(p));
  }
  printf("\n");
}

int main() {
  ul_t n, k;
  while (scanf("%llu %llu", &n, &k) != EOF) {
    // printf("loop\n");
    set_size(n);
    memset(tree, 1, interval_size);
    for (ul_t i = 0; i < n; i ++) {
      int t;
      scanf("%d", &t);
      char s = sgn(t);
      set(i, s);
    }
    char buf[100];

    for (int i = 0; i < k; i ++) {
      long long a, b;
      scanf("%s %lld %lld", buf, &a, &b);
      if (buf[0] == 'C') {
        set(a - 1, sgn(b));
        // printf("buffer: %s %lld %lld\n", buf, a, b);
        // printf("setting %lu to %s\n", a, show(b));
        // show_state(n);
      } else {
        char p = query(a - 1, b - 1);
        printf("%s", show(p));
      }
    }
    printf("\n");
  }
}

