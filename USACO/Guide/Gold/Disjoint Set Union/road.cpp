#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;

I pars[N];
I sizs[N];
I siz = 0;
I cnt;

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
  cnt--;
  siz = max(siz, sizs[a]);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("road.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  cnt = n;
  fill_n(pars, n, -1);
  fill_n(sizs, n, 1);
  while (m--) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    uni(a, b);
    printf("%i %i\n", cnt, siz);
  }
  return 0;
}