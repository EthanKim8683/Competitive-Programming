#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 100000;

pair<I, I> cows[N];

I main(void) {
#ifndef ETHANKIM8683
  freopen("pairup.in", "r", stdin);
  freopen("pairup.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x, y;
    cin >> x >> y;
    cows[i] = {y, x};
  }
  sort(cows, cows + n);
  I l = 0;
  I r = n - 1;
  I res = 0;
  while (l < r) {
    const auto [l_rte, l_cnt] = cows[l];
    const auto [r_rte, r_cnt] = cows[r];
    res = max(res, l_rte + r_rte);
    const I cnt = min(l_cnt, r_cnt);
    if ((cows[l].second -= cnt) == 0)
      l++;
    if ((cows[r].second -= cnt) == 0)
      r--;
  }
  if (l == r)
    res = max(res, cows[l].first * 2);
  printf("%i\n", res);
  return 0;
}