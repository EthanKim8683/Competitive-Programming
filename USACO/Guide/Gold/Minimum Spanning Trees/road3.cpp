#include <iostream>
#include <cstdio>
#include <tuple>
#include <algorithm>
#include <unordered_set>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I MAX = 1e9;
const I N = 1e5;
const I M = 2e5;

tuple<I, I, I> edgs[M];
pair<I, I> mins[N];
unordered_set<I> coms;
I pars[N];

I fnd(I i) {
  if (pars[i] < 0)
    return i;
  return pars[i] = fnd(pars[i]);
}

B uni(I a, I b) {
  if ((a = fnd(a)) == (b = fnd(b)))
    return false;
  if (pars[a] > pars[b]) {
    const I t = a;
    a = b;
    b = t;
  }
  pars[a] += pars[b];
  pars[b] = a;
  return true;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("road3.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  fill_n(pars, n, -1);
  for (I i = 0; i < n; i++)
    coms.insert(i);
  for (I i = 0; i < m; i++) {
    I a, b, c;
    cin >> a >> b >> c;
    edgs[i] = {a - 1, b - 1, c};
  }
  Lli res = 0;
  fill_n(mins, n, pair<I, I>{MAX, -1});
  while (coms.size() > 1) {
    B psb = false;
    for (I i = 0; i < m; i++) {
      auto [a, b, c] = edgs[i];
      if ((a = fnd(a)) != (b = fnd(b))) {
        psb = true;
        if (c < mins[a].first)
          mins[a] = {c, b};
        if (c < mins[b].first)
          mins[b] = {c, a};
      }
    }
    if (!psb) {
      printf("IMPOSSIBLE\n");
      return 0;
    }
    for (const auto a : coms) {
      const auto [dst, b] = mins[a];
      if (dst != MAX && uni(a, b))
        res += dst;
    }
    for (auto it = coms.begin(); it != coms.end();) {
      if (pars[*it] < 0)
        mins[*it++].first = MAX;
      else
        it = coms.erase(it);
    }
  }
  printf("%lli\n", res);
  return 0;
}