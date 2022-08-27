#include <iostream>
#include <cstdio>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1000;
const I M = 300000;
const I K = 10000;

I pars[K][N];
tuple<I, I, I, I> edgs[M];
I ress[M];

I fnd(I pars[], I i) {
  if (pars[i] < 0)
    return i;
  return pars[i] = fnd(pars, pars[i]);
}

void uni(I pars[], I a, I b) {
  if ((a = fnd(pars, a)) == (b = fnd(pars, b)))
    return;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
}

B con(I pars[], I a, I b) {
  return fnd(pars, a) == fnd(pars, b);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("inheritance.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, k;
  cin >> n >> m >> k;
  for (I i = 0; i < k; i++)
    fill_n(pars[i], n, -1);
  for (I i = 0; i < m; i++) {
    I a, b, c;
    cin >> a >> b >> c;
    edgs[i] = {c, a - 1, b - 1, i};
  }
  sort(edgs, edgs + m, greater<tuple<I, I, I, I>>());
  for (I i = 0; i < m; i++) {
    const auto [c, a, b, j] = edgs[i];
    I l = 0;
    I r = k;
    while (l < r) {
      const I m = l + (r - l) / 2;
      if (con(pars[m], a, b))
        l = m + 1;
      else
        r = m;
    }
    if (l != k) {
      ress[j] = l + 1;
      uni(pars[l], a, b);
    }
  }
  for (I i = 0; i < m; i++)
    printf("%i\n", ress[i]);
  return 0;
}