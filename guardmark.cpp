#include <iostream>
#include <stdio.h>
#include <string.h>

#define NMAX 0x100000
#define max(_x, _y) (_x < _y ? _y : _x)

typedef unsigned long ul_t;

long long weight[20];
long long height[20];
long long strength[20];

long long safety[NMAX];
long long total_weight[NMAX];
long long total_height[NMAX];

ul_t masks[20];

using namespace std;

void fill_masks() {
  for (int i = 0; i < 20; i++) {
    masks[i] = 0xFFFFF ^ (1 << i);
    // printf("%lx ", masks[i]);
  }
}

void run () {
  long long H, ans;
  int n;
  ans = -1;
  cin >> n >> H;
  for (int i = 0; i < n; i++) {
    cin >> height[i] >> weight[i] >> strength[i];
  }

  ul_t full_set = 1 << n;
  safety[0] = 0xFFFFFFFFFFF;
  total_height[0] = 0;
  total_weight[0] = 0;

  for (ul_t i = 0; i < full_set; i++) {
    for (int j = 0; j < n; j++) {
      ul_t m = i & masks[j];
      if (m != i) {
        long long s = strength[j] - total_weight[m];
        s = s < safety[m] ? s : safety[m];
        if (s >= 0) {
          long long w = total_weight[m] + weight[j];
          long long h = total_height[m] + height[j];
          // printf("Extending set %lx with cow nr %d. Safety: %ld, Height: %ld\n", m, j, s, h);
          if (h >= H) ans = max(ans, s);
          if (s > safety[i]) {
            safety[i] = s;
            total_weight[i] = w;
            total_height[i] = h;
          }
        }
      }
    }
  }

  if (ans > 0) {
    cout << ans << "\n";
  } else {
    cout << "Mark is too tall\n";
  }
}

int main () {
  memset(safety, 0xFF, sizeof(safety));
  fill_masks();
  run();
  return 0;
}