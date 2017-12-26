#include <stdlib.h>
#include <stdio.h>

void print_cams(char* cameras, long n, long t, long h) {
  for (long i = 0; i < n; i ++) {
    printf("%c", cameras[i] ? 'C' : '.');
  }
  printf("\n");
  for (long i = 0; i < t; i ++) {
    printf(" ");
  }
  printf("^");
  for (long i = t + 1; i < h; i ++) printf(" ");
  printf("^\n\n");
}

int main () {
  long n, k, r;
  int res = scanf("%ld %ld %ld", &n, &k, &r);

  char *cameras = (char *) calloc(n, sizeof(char));
  for (long i = 0; i < k; i ++) {
    long t;
    res = scanf("%ld", &t);
    cameras[t-1] = 1;
  }

  long added = 0;
  long t = 0;
  long h = t;
  long count = 0;
  for (; h < r; h ++) count += cameras[h];
  h--;
  // print_cams(cameras, n, t, h);
  // printf("%ld\n", h);

  int tmp = h;
  while (count < 2) {
    count += 1 - cameras[tmp];
    added += 1 - cameras[tmp];
    cameras[tmp] = 1;
    tmp --;
  }

  // print_cams(cameras, n, t, h);

  while (h < n - 1) {
    count += cameras[++h];
    count -= cameras[t++];
    if (count < 2) {
      cameras[h] = 1;
      count ++;
      added ++;
    }
    // printf("count: %ld\n", count);
    // print_cams(cameras, n, t, h);
  }

  free(cameras);
  printf("%ld", added);
}