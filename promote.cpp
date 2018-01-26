#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 100000
#define NOPRED 100001

#define TREESIZE 0x40000
#define TREEM 0x1FFFF

typedef unsigned long ul_t;
typedef long prof_t;

typedef struct cow_list {
  ul_t idx;
  struct cow_list *next;
} cow_list_t;

typedef struct cow {
  prof_t      prof;
  ul_t        inv;
  cow_list_t *children;
} cow_t;

typedef struct cow_sortable {
  prof_t prof;
  prof_t idx;
} cow_s_t;

int cow_compare(const void *a, const void *b) {
  prof_t diff = ((cow_s_t*) a)->prof - ((cow_s_t*) b)->prof;
  if (diff <  0) return -1;
  if (diff == 0) return 0;
  return 1;
}

cow_t  *cows              = (cow_t*) calloc(NMAX, sizeof(cow_t));
cow_s_t sorted_cows[NMAX];
ul_t   *tree              = (ul_t*) calloc(TREESIZE, sizeof(ul_t));

ul_t query(ul_t a, ul_t b) {
  ul_t va = TREEM + a;
  ul_t vb = TREEM + b;
  ul_t res = tree[va];
  if (vb != va) res += tree[vb];
  do {
    ul_t apred = (va - 1) / 2;
    ul_t bpred = (vb - 1) / 2;
    if (apred == bpred) break;
    if (va % 2 == 1) res += tree[va + 1];
    if (vb % 2 == 0) res += tree[vb - 1];
    va = apred; vb = bpred;
  } while (1);
  return res;
}

void set(ul_t x) {
  ul_t vx = TREEM + x;
  tree[vx] = 1;
  while (vx != 0) {
    vx = (vx - 1) / 2;
    tree[vx] = tree[2 * vx + 1] + tree[2 * vx + 2];
  }
}

void check(ul_t idx, ul_t prev) {
  cow_list_t *e = cows[idx].children;
  // printf("checking chlidren of %lu\n", idx);
  while (e != NULL) {
    prof_t p = cows[e->idx].prof;
    ul_t   t = query(p + 1, NMAX);
    // printf("child: %lu, current sum %lu\n", e->idx, t);
    check(e->idx, t);
    e = e->next;
  }

  // printf("done checking %lu\n", idx);
  set(cows[idx].prof);
  cows[idx].inv = query(cows[idx].prof + 1, NMAX) - prev;
} 

int main() {
  prof_t n;
  scanf("%lu", &n);
  for (prof_t i = 0; i < n; i ++) {
    prof_t p;
    scanf("%lu", &p);
    sorted_cows[i].prof = p;
    sorted_cows[i].idx = i;
  }

  qsort(sorted_cows, n, sizeof(cow_s_t), cow_compare);

  for (ul_t i = 0; i < n; i ++) {
    cows[sorted_cows[i].idx].prof = i;
  }

  for (prof_t i = 1; i < n; i ++) {
    prof_t p;
    scanf("%lu", &p);
    p --;
    cow_list_t *e = (cow_list_t *) malloc(sizeof(cow_list_t));
    e->idx = i;
    e->next = cows[p].children;
    cows[p].children = e;
  }

  check(0, 0);

  // for (prof_t i = 0; i < n; i ++) {
  //   printf("cow %lu: prof - %lu, inv - %lu, pred - %lu\n",
  //     i, cows[i].cow_prof, cows[i].inv, cows[i].pred);
  // }

  for (prof_t i = 0; i < n; i ++) {
    printf("%lu\n", cows[i].inv);
  }
}


