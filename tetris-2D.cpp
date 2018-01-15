#include <stdio.h>
#include <stdlib.h>

#define NMAX 0x200000

typedef unsigned long ul_t;

typedef struct {
  ul_t height;
  ul_t child_max;
} node_t;

node_t *tree = (node_t *) calloc(NMAX, sizeof(node_t));

#define left_child(_n) (_n * 2)
#define right_child(_n) (_n * 2 + 1)
#define max(_a, _b) (_a < _b ? _b : _a)

ul_t query_inner(ul_t q_l, ul_t q_r, ul_t i_l, ul_t i_r, ul_t node) {
  ul_t m = (i_l + i_r) / 2;

  if (q_l == i_l && q_r == i_r) {
    // base case
    return max(tree[node].height, tree[node].child_max);
  }

  if (q_l <= m) {
    if (q_r <= m) {
      // [q_l, q_r] is contained in left subinterval
      ul_t sub_max = query_inner(q_l, q_r, i_l, m, left_child(node));
      return max(sub_max, tree[node].height);
    } else {
      // [q_l, q_r] is split into [q_l, m] and [m+1, q_r]
      ul_t left_max = query_inner(q_l, m, i_l, m, left_child(node));
      ul_t right_max = query_inner(m + 1, q_r, m + 1, i_r, right_child(node));
      ul_t child_max = max(left_max, right_max);
      return max(child_max, tree[node].height);
    }
  } else {
      // [q_l, q_r] is contained in right subinterval
      ul_t right_max = query_inner(q_l, q_r, m + 1, i_r, right_child(node));
      return max(right_max, tree[node].height);
  }
}

void add_interval_inner(ul_t q_l, ul_t q_r, ul_t i_l, ul_t i_r, ul_t node, ul_t val) {
  ul_t m = (i_l + i_r) / 2 + 1;

  if (q_l == i_l && q_r == i_r) {
    // base case
    tree[node].height = max(tree[node].height, val);
    return;
  }

  tree[node].child_max = max(val, tree[node].child_max);

  if (q_l < m) {
    if (q_r < m) {
      // [q_l, q_r] is contained in left subinterval
      add_interval_inner(q_l, q_r, i_l, m - 1, left_child(node), val);
      return;
    } else {
      // [q_l, q_r] is split into [q_l, m-1] and [m, q_r]
      add_interval_inner(q_l, m - 1, i_l, m - 1, left_child(node), val);
      add_interval_inner(m, q_r, m, i_r, right_child(node), val);
      return;
    }
  } else {
      // [q_l, q_r] is contained in right subinterval
      add_interval_inner(q_l, q_r, m, i_r, right_child(node), val);
      return;
  }
}

ul_t query(ul_t l, ul_t r) {
  return query_inner(l, r, 0, 0x100000 - 1, 1);
}


void add_interval(ul_t l, ul_t r, ul_t val) {
  add_interval_inner(l, r, 0, 0x100000 - 1, 1, val);
}

int main () {
  ul_t d, n;
  scanf("%lu %lu", &d, &n);
  for (ul_t i = 0; i < n; i ++) {
    ul_t x, len;
    scanf("%lu %lu", &len, &x);
    ul_t l = x;
    ul_t r = l + len - 1;
    // printf("l = %lu r = %lu\n", l, r);
    ul_t m = query(l, r);
    // printf("m = %lu\n", m);
    add_interval(l, r, m + 1);
  }

  ul_t m = query(0, d);
  printf("%lu", m);
  return 0;
}