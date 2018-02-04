#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <vector>

#define MMAX 1000000

using namespace std;

vector<char> edges[1000];
vector<long> flips[1000];

void print_flips(int n) {
  for (int i = 0; i < n - 1; i ++) {
    for (int j = 0; j < n - i - 1; j ++) {
      printf("%ld ", flips[i][j]);
    }
    printf("\n");
  }
}

void allocate_vectors(int n) {
  for (int i = 0; i < n - 1; i ++) {
    edges[i].reserve(n - i - 1);
    flips[i].reserve(n - i - 1);
    bzero(edges[i].data(), n - i - 1);
  }
}

void prepare(long n) {
  for (long i = 0; i < n - 1; i ++) {
    for (long j = 0; j < n - i - 1; j ++) {
      flips[i][j] = edges[i][j];
    }
  }
}

void flip(long n, long i) {
  // printf("flipping %ld\n", i);
  // print_flips(n);
  for (long j = 0; j < i; j ++) {
    flips[j][i - j - 1] += 1;
  }
  for (long j = 0; j < n - i - 1; j ++) {
    flips[i][j] += 1;
  }
  // print_flips(n);
  // printf("\n");
}

int check(long n, long first) {
  for (long i = 0; i < n - 1; i ++) {
    flips[0][i] += first;
  }

  for (long i = 1; i < n - 1; i ++) {
    for (long j = 0; j < i; j ++) {
      if (flips[j][i - j - 1] % 2 == 0) {
        flip(n, i);
        break;
      }
    }
  }

  for (long i = 0; i < n - 1; i ++) {
    for (long j = 0; j < n - i - 1; j ++) {
      if (flips[i][j] % 2 == 0)
        return 0;
    }
  }
  return 1;
}

int main () {
  long n, m;
  scanf("%ld %ld", &n, &m);
  allocate_vectors(n);
  for (long i = 0; i < m; i ++) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    if (b < a) {
      long t = b;
      b = a;
      a = t;
    }
    edges[a - 1][b - a - 1] = 1;
  }
  int res = 0;
  prepare(n);
  // print_flips(n);
  res = check(n, 1);
  // print_flips(n);
  if (!res) {
    prepare(n);
    res = check(n, 0);
    // print_flips(n);
  }
  if (res) printf("DA\n");
  else printf("NE\n");

  return 0;
}