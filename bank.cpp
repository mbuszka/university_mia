#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <queue>
#include <stack>
#include <functional>

typedef long long ll_t;

using namespace std;

char deleted[1000000];

void run() {
  priority_queue<long, vector<long>, greater<long> > contents;
  vector<long> envelopes;
  long n;
  ll_t s;
  scanf("%ld %lld", &n, &s);

  bzero(deleted, 1000000);

  for (long i = 0; i < n; i++) {
    long op;
    scanf("%ld", &op);
    if (op > 0) {
      contents.push(op);
      envelopes.push_back(op);
      deleted[op] = 0;
    } else {
      op = - op;
      if (!contents.empty() && contents.top() > op) {
        s -= op;
      } else {
        long acc = - op;
        while (acc < 0 && !envelopes.empty()) {
          acc += envelopes.back();
          deleted[envelopes.back()] = 1;
          envelopes.pop_back();
        }
        s += acc;
        while (!contents.empty() && deleted[contents.top()]) contents.pop();
      }
    }
  }
  ll_t a = 0;
  for (long i = 0; i < envelopes.size(); i++) {
    a += envelopes[i];
  }

  printf("%lld %lld\n", s, a);
}

int main () {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    run();
  }


}