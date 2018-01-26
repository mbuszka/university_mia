#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 100000
#define NOPRED 100001

typedef unsigned long prof_t;

typedef struct {
  prof_t cow_prof;
  prof_t pred;
  prof_t inv;
} cow_t;

cow_t cows[NMAX];

int main() {
  prof_t n;
  scanf("%lu", &n);
  for (prof_t i = 0; i < n; i ++) {
    prof_t p;
    scanf("%lu", &p);
    cows[i].cow_prof = p;
    cows[i].inv = 0;
  }

  cows[0].pred = NOPRED;

  for (prof_t i = 1; i < n; i ++) {
    prof_t p;
    scanf("%lu", &p);
    cows[i].pred = p - 1;
  }

  for (prof_t i = 1; i < n; i++) {
    prof_t prof = cows[i].cow_prof;
    prof_t p = cows[i].pred;
    while (p != NOPRED) {
      if (cows[p].cow_prof < prof) {
        cows[p].inv ++;
      }
      p = cows[p].pred;
    }
  }

  // for (prof_t i = 0; i < n; i ++) {
  //   printf("cow %lu: prof - %lu, inv - %lu, pred - %lu\n",
  //     i, cows[i].cow_prof, cows[i].inv, cows[i].pred);
  // }

  for (prof_t i = 0; i < n; i ++) {
    printf("%lu\n", cows[i].inv);
  }
}


