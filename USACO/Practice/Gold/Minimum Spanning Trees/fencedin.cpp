#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 2000;
const I M = 2000;

I a_arr[N + 1];
I b_arr[M + 1];
tuple<I, I, I> edgs[N * (M + 1) + M * (N + 1)];
I pars[(N + 1) * (M + 1)];
I rnks[(N + 1) * (M + 1)];
I m;

I cps(I i, I j) {
  return i * (m + 1) + j;
}

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
  freopen("fencedin.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("fencedin.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I a, b, n;
  cin >> a >> b >> n >> m;
  fill_n(pars, (n + 1) * (m + 1), -1);
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < m; i++)
    cin >> b_arr[i];
  a_arr[n] = a;
  b_arr[m] = b;
  sort(a_arr, a_arr + n + 1);
  sort(b_arr, b_arr + m + 1);
  I len = 0;
  I lst = 0;
  for (I i = 0; i <= n; i++) {
    const auto nxt = a_arr[i];
    const I dst = nxt - lst;
    for (I j = 0; j < m; j++)
      edgs[len++] = {dst, cps(i, j), cps(i, j + 1)};
    lst = nxt;
  }
  lst = 0;
  for (I i = 0; i <= m; i++) {
    const auto nxt = b_arr[i];
    const I dst = nxt - lst;
    for (I j = 0; j < n; j++)
      edgs[len++] = {dst, cps(j, i), cps(j + 1, i)};
    lst = nxt;
  }
  sort(edgs, edgs + len);
  Lli res = 0;
  for (I i = 0; i < len; i++) {
    const auto [dst, a, b] = edgs[i];
    if (uni(a, b))
      res += dst;
  }
  printf("%lli\n", res);
  return 0;
}