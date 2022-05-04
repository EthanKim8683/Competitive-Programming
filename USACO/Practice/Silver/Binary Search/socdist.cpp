#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I M = 1e5;

pair<Lli, Lli> grass[M];
I n, m;

B check(Lli d) {
  I cnt = 0;
  Lli lst = 0;
  for (I i = 0; i < m; i++) {
    const auto [a, b] = grass[i];
    Lli j = max(a, lst);
    while (j <= b) {
      cnt++;
      if (cnt >= n)
        return true;
      j += d;
    }
    lst = j;
  }
  return false;
}

I main(void) {
  freopen("socdist.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("socdist.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (I i = m; i--;) {
    Lli a, b;
    cin >> a >> b;
    grass[i] = {a, b};
  }
  sort(grass, grass + m);
  Lli l = 1;
  Lli r = 1e18;
  while (l < r) {
    const Lli m = l + (r - l + 1) / 2;
    if (check(m))
      l = m;
    else
      r = m - 1;
  }
  printf("%lli\n", l);
  return 0;
}