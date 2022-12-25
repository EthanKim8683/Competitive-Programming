#include <iostream>
#include <cstdio>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;

const I N = 500;

tuple<I, I, I> dsts[2 * N * N];
I hgts[N * N];
I pars[N * N];
I sizs[N * N];
I n;

I cps(I r, I c) {
  return r * n + c;
}

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
    const I t = a;
    a = b;
    b = t;
  }
  pars[b] = a;
  sizs[a] += sizs[b];
}

I main(void) {
  freopen("tractor.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("tractor.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  fill_n(pars, n * n, -1);
  fill_n(sizs, n * n, 1);
  for (I i = 0; i < n * n; i++)
    cin >> hgts[i];
  I len = 0;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < n; j++) {
      const auto cur = cps(i, j);
      if (i + 1 < n) {
        const auto nxt = cps(i + 1, j);
        dsts[len++] = {abs(hgts[cur] - hgts[nxt]), cur, nxt};
      }
      if (j + 1 < n) {
        const auto nxt = cps(i, j + 1);
        dsts[len++] = {abs(hgts[cur] - hgts[nxt]), cur, nxt};
      }
    }
  }
  if (len != 0) {
    sort(dsts, dsts + len);
    const I thr = (n * n + 1) / 2;
    for (I i = 0; i < len; i++) {
      const auto [dst, a, b] = dsts[i];
      uni(a, b);
      if (sizs[fnd(a)] >= thr) {
        printf("%i\n", dst);
        break;
      }
    }
  } else
    printf("0\n");
  return 0;
}