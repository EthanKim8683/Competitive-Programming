#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 200000;

I pars[N];
I deps[N];

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
  if (deps[a] > deps[b]) {
    const auto t = a;
    a = b;
    b = t;
  }
  deps[a] += deps[b];
  pars[b] = a;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("unionfind.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  fill_n(pars, n, -1);
  while (q--) {
    I t, u, v;
    cin >> t >> u >> v;
    if (t == 0)
      uni(u, v);
    else if (t == 1)
      printf("%i\n", fnd(u) == fnd(v));
  }
  return 0;
}