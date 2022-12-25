#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

using I = int;

const I N = 100000;

I stts[N + 1];
I deps[N + 1];
stack<I> acts;

I main(void) {
  freopen("art2.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("art2.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  acts.push(0);
  stts[0] = 1;
  for (I i = 0; i < n; i++) {
    I c;
    cin >> c;
    switch (stts[c]) {
      case 0:
        acts.push(c);
        stts[c] = 1;
        break;
      case 1: {
        auto dep = deps[c];
        while (acts.top() != c) {
          const auto act = acts.top();
          stts[act] = 2;
          dep = max(dep, deps[act] + 1);
          acts.pop();
        }
        deps[c] = dep;
        break;
      }
      case 2:
        printf("-1");
        return 0;
    }
  }
  I res = deps[0];
  while (acts.top() != 0) {
    res = max(res, deps[acts.top()] + 1);
    acts.pop();
  }
  printf("%i\n", res);
  return 0;
}