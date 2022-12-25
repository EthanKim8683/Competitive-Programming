#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;

const I N = 1000;

pair<I, I> cows[N];
tuple<I, I, I> dsts[N * N];
I pars[N];
I sizs[N];

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
  freopen("moocast.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("moocast.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, n, -1);
  fill_n(sizs, n, 1);
  for (I i = 0; i < n; i++) {
    I x, y;
    cin >> x >> y;
    cows[i] = {x, y};
  }
  I len = 0;
  for (I i = 0; i < n - 1; i++) {
    const auto [i_x, i_y] = cows[i];
    for (I j = i + 1; j < n; j++) {
      const auto [j_x, j_y] = cows[j];
      const I dx = i_x - j_x;
      const I dy = i_y - j_y;
      dsts[len++] = {dx * dx + dy * dy, i, j};
    }
  }
  sort(dsts, dsts + len);
  for (I i = 0; i < len; i++) {
    const auto [dst, a, b] = dsts[i];
    uni(a, b);
    if (sizs[fnd(a)] == n) {
      printf("%i\n", dst);
      break;
    }
  }
  return 0;
}