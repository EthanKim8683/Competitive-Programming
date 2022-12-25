#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 2000;

tuple<I, I, I> edgs[N * N];
I tems[N];
I pars[N];
I rnks[N];

I fnd(I i) {
  if (pars[i] == -1)
    return i;
  return pars[i] = fnd(pars[i]);
}

B uni(I a, I b) {
  a = fnd(a);
  b = fnd(b);
  if (a == b)
    return false;
  if (rnks[a] < rnks[b]) {
    const I t = a;
    a = b;
    b = t;
  }
  pars[b] = a;
  if (rnks[a] == rnks[b])
    rnks[a]++;
  return true;
}

I main(void) {
  freopen("superbull.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("superbull.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, n, -1);
  for (I i = 0; i < n; i++)
    cin >> tems[i];
  I len = 0;
  for (I i = 0; i < n; i++)
    for (I j = i + 1; j < n; j++)
      edgs[len++] = {tems[i] ^ tems[j], i, j};
  sort(edgs, edgs + len, greater<tuple<I, I, I>>());
  Lli res = 0;
  for (I i = 0; i < len; i++) {
    const auto [pnt, a, b] = edgs[i];
    if (uni(a, b))
      res += pnt;
  }
  printf("%lli\n", res);
  return 0;
}