#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 1e5;
const I M = 2e5;

I pars[N];
I rnks[N];
tuple<I, I, I> edgs[M];

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
#ifdef ETHANKIM8683
  freopen("road.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  fill_n(pars, n, -1);
  for (I i = 0; i < m; i++) {
    I a, b, c;
    cin >> a >> b >> c;
    edgs[i] = {c, a, b};
  }
  sort(edgs, edgs + m);
  Lli cst = 0;
  I cnt = 0;
  for (I i = 0; i < m; i++) {
    const auto [c, b, a] = edgs[i];
    if (uni(a, b)) {
      cst += c;
      cnt++;
    }
  }
  if (cnt == n - 1)
    printf("%lli\n", cst);
  else
    printf("IMPOSSIBLE\n");
  return 0;
}