#include <iostream>
#include <cstdio>
#include <numeric>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

pair<I, I> peks[N];
B viss[N];
I inds[N];

B cmp(pair<I, I> a, pair<I, I> b) {
  return a.second > b.second;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("mountains.in", "r", stdin);
  freopen("mountains.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x, y;
    cin >> x >> y;
    peks[i] = {x, y};
  }
  sort(peks, peks + n, cmp);
  I res = 0;
  for (I i = 0; i < n; i++) {
    if (!viss[i]) {
      res++;
      const auto [x0, y0] = peks[i];
      for (I j = i + 1; j < n; j++) {
        const auto [x1, y1] = peks[j];
        if (abs(x0 - x1) <= y0 - y1)
          viss[j] = true;
      }
    }
  }
  printf("%i\n", res);
  return 0;
}