#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char word[55];

int max (int *lis, int idx) {
  int t = 0;
  for (int i = 0; i < idx; i ++) {
    t = t < lis[i] ? lis[i] : t;
  }
  return t;
}

int main () {
  int r = scanf("%s", word);
  int n = strlen(word);

  int *lis = (int *) calloc(26, sizeof(int));
  
  for (int i = 0; i < n; i ++) {
    int off = word[i] - 'a';
    // printf("off %d\n", off);
    int m = max(lis, off);
    // printf("m %d\n", m);
    lis[off] = m >= lis[off] ? m + 1 : lis[off];
  }

  printf("%d", 26 - max(lis, 26));

  free(lis);
  return 0;
}