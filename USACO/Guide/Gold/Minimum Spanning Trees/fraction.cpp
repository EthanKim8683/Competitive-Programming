#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

using I = int;
using Lf = long double;
using B = bool;

const I N = 1e5;
const I ITR = 20;
const Lf MIN = -1e18;

vector<tuple<I, I, I>> adjs[N];
priority_queue<tuple<Lf, I, I, I>> que;
Lf dsts[N];
B viss[N];
I a_tot, b_tot;
I n;

B tst(Lf c) {
  Lf dst_tot = 0;
  a_tot = 0;
  b_tot = 0;
  fill_n(dsts, n, MIN);
  fill_n(viss, n, false);
  que.push({dsts[0] = 0, 0, 0, 0});
  while (!que.empty()) {
    const auto [dst, a, b, i] = que.top();
    que.pop();
    if (!viss[i]) {
      viss[i] = true;
      dst_tot += dst;
      a_tot += a;
      b_tot += b;
      for (const auto [j, a, b] : adjs[i])
        if (a - b * c > dsts[j])
          que.push({dsts[j] = a - b * c, a, b, j});
    }
  }
  return dst_tot >= 0;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("fraction.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I u, v, a, b;
    cin >> u >> v >> a >> b;
    adjs[u].push_back({v, a, b});
    adjs[v].push_back({u, a, b});
  }
  Lf l = 0;
  Lf r = 101;
  for (I i = 0; i < ITR; i++) {
    const Lf m = (l + r) / 2;
    if (tst(m))
      l = m;
    else
      r = m;
  }
  I fac = gcd(a_tot, b_tot);
  printf("%i/%i\n", a_tot / fac, b_tot / fac);
  return 0;
}