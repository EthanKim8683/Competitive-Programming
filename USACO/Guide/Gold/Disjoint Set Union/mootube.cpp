#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100000;
const I Q = 100000;

tuple<I, I, I> rels[N];
tuple<I, I, I> qrys[Q];
I pars[N];
I sizs[N];
I ress[N];

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
  if (sizs[a] < sizs[b]) {
    const auto t = a;
    a = b;
    b = t;
  }
  sizs[a] += sizs[b];
  pars[b] = a;
}

I main(void) {
  freopen("mootube.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("mootube.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  fill_n(pars, n, -1);
  fill_n(sizs, n, 1);
  for (I i = 0; i < n - 1; i++) {
    I a, b, r;
    cin >> a >> b >> r;
    rels[i] = {r, a - 1, b - 1};
  }
  for (I i = 0; i < q; i++) {
    I k, v;
    cin >> k >> v;
    qrys[i] = {k, v - 1, i};
  }
  sort(rels, rels + n, greater<tuple<I, I, I>>());
  sort(qrys, qrys + q, greater<tuple<I, I, I>>());
  I ind = 0;
  for (I i = 0; i < n - 1; i++) {
    const auto [r, a, b] = rels[i];
    while (ind < q && r < get<0>(qrys[ind])) {
      const auto [k, v, i] = qrys[ind++];
      ress[i] = sizs[fnd(v)] - 1;
    }
    uni(a, b);
  }
  while (ind < q) {
    const auto [k, v, i] = qrys[ind++];
    ress[i] = sizs[fnd(v)] - 1;
  }
  for (I i = 0; i < q; i++)
    printf("%i\n", ress[i]);
  return 0;
}