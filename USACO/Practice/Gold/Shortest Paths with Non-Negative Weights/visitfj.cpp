#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MAX = 1e9;
const I N = 100;

I tims[N * N];
Lli dsts[3][N * N];
priority_queue<tuple<Lli, I, I>, vector<tuple<Lli, I, I>>, greater<tuple<Lli, I, I>>> que;
I n;

I cps(I i, I j) {
  return i * n + j;
}

pair<I, I> exp(I i) {
  return {i / n, i % n};
}

I main(void) {
  freopen("visitfj.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("visitfj.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> n >> t;
  for (I i = 0; i < 3; i++)
    fill_n(dsts[i], n * n, MAX);
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      cin >> tims[cps(i, j)];
  que.push({dsts[0][cps(0, 0)] = 0, 0, 0});
  while (!que.empty()) {
    const auto [dst, a, fld] = que.top();
    que.pop();
    const auto a_dst = dst;
    const auto a_fld = fld;
    if (dst == dsts[fld][a]) {
      const auto [i, j] = exp(a);
      const auto trv = [=](I b) {
        I b_dst = a_dst + t;
        I b_fld = a_fld + 1;
        if (a_fld == 2) {
          b_dst += tims[b];
          b_fld = 0;
        }
        if (b_dst < dsts[b_fld][b])
          que.push({dsts[b_fld][b] = b_dst, b, b_fld});
      };
      if (i - 1 >= 0)
        trv(cps(i - 1, j));
      if (i + 1 < n)
        trv(cps(i + 1, j));
      if (j - 1 >= 0)
        trv(cps(i, j - 1));
      if (j + 1 < n)
        trv(cps(i, j + 1));
    }
  }
  const I ind = cps(n - 1, n - 1);
  Lli res = MAX;
  res = min(res, dsts[0][ind]);
  res = min(res, dsts[1][ind]);
  res = min(res, dsts[2][ind]);
  printf("%lli\n", res);
  return 0;
}