#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100000;

pair<I, I> hbls[N];
multiset<I> spcs;

I main(void) {
  freopen("hayfeast.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("hayfeast.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  Lli m;
  cin >> n >> m;
  for (I i = 0; i < n; i++) {
    I f, s;
    cin >> f >> s;
    hbls[i] = {f, s};
  }
  I l = 0;
  I r = 0;
  Lli flv = 0;
  I res = 1e9;
  while (r <= n) {
    if (flv >= m) {
      res = min(res, *spcs.rbegin());
      const auto [f, s] = hbls[l++];
      flv -= f;
      spcs.erase(spcs.find(s));
    } else {
      if (r >= n)
        break;
      const auto [f, s] = hbls[r++];
      flv += f;
      spcs.insert(s);
    }
  }
  printf("%i\n", res);
  return 0;
}