#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;
const I M = 1e5;

tuple<I, I, I> wrms[M];
I cnts[N];
I pars[N];
I rnks[N];

I fnd(I i) {
  if (pars[i] == -1)
    return i;
  return pars[i] = fnd(pars[i]);
}

void uni(I a, I b) {
  a = fnd(a);
  b = fnd(b);
  if (a == b)
    return;
  if (rnks[a] < rnks[b]) {
    const I t = a;
    a = b;
    b = t;
  }
  pars[b] = a;
  cnts[a] += cnts[b];
  if (rnks[a] == rnks[b])
    rnks[a]++;
}

I main(void) {
  freopen("wormsort.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("wormsort.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  fill_n(pars, n, -1);
  I cnt = 0;
  for (I i = 0; i < n; i++) {
    I p;
    cin >> p;
    if (p - 1 != i) {
      cnts[i] = 1;
      cnt++;
    }
  }
  for (I i = 0; i < m; i++) {
    I a, b, w;
    cin >> a >> b >> w;
    wrms[i] = {w, a - 1, b - 1};
  }
  if (cnt != 0) {
    sort(wrms, wrms + m, greater<tuple<I, I, I>>());
    for (I i = 0; i < m; i++) {
      const auto [w, a, b] = wrms[i];
      uni(a, b);
      if (cnts[fnd(a)] == cnt) {
        printf("%i\n", w);
        break;
      }
    }
  } else
    printf("-1\n");
  return 0;
}