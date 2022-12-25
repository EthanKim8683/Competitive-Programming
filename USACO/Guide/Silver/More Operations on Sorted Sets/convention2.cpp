#include <iostream>
#include <cstdio>
#include <tuple>
#include <queue>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

priority_queue<tuple<I, I, I>, vector<tuple<I, I, I>>, greater<tuple<I, I, I>>> cows;
priority_queue<tuple<I, I, I>, vector<tuple<I, I, I>>, greater<tuple<I, I, I>>> wais;

I main(void) {
#ifndef ETHANKIM8683
  freopen("convention2.in", "r", stdin);
  freopen("convention2.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a, t;
    cin >> a >> t;
    cows.push({a, i, t});
  }
  I res = 0;
  I end = -1;
  while (!cows.empty() || !wais.empty()) {
    while (!cows.empty()) {
      const auto [a, i, t] = cows.top();
      if (a > end && !wais.empty())
        break;
      cows.pop();
      wais.push({i, a, t});
    }
    const auto [i, a, t] = wais.top();
    wais.pop();
    res = max(res, end - a);
    end = max(end, a) + t;
  }
  printf("%i\n", res);
  return 0;
}