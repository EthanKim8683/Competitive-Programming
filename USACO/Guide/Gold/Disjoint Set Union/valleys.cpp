#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

/*
Only one region is affected for each union.
Also, each union introduces a completely
new valley.
Combine this with the fact that each union
may introduce a hole, we can, for each new
region, determine whether it contributes to
the final result.
*/

const I N = 750;

I cels[N][N];
I pars1[N * N + 1];
I pars2[N * N];
I pars3[N * N];
B viss1[N * N + 1];
B viss2[N * N];
B viss3[N * N];
tuple<I, I, I> vals[N * N];
I nets[N * N];
I sizs[N * N];
I hols[N * N];
I cnt1 = 0;
I n;

I cps(I i, I j) {
  return i * n + j;
}

B bnd(I i, I j) {
  return i >= 0 && i < n && j >= 0 && j < n;
}

I fnd1(I x) {
  if (pars1[x] < 0)
    return x;
  return pars1[x] = fnd1(pars1[x]);
}

I fnd2(I x) {
  if (pars2[x] < 0)
    return x;
  return pars2[x] = fnd2(pars2[x]);
}

I fnd3(I x) {
  if (pars3[x] < 0)
    return x;
  return pars3[x] = fnd3(pars3[x]);
}

void uni1(I a, I b) {
  if (!viss1[a] || !viss1[b])
    return;
  if ((a = fnd1(a)) == (b = fnd1(b)))
    return;
  if (pars1[a] > pars1[b])
    swap(a, b);
  pars1[a] += pars1[b];
  pars1[b] = a;
  cnt1--;
}

void uni2(I a, I b) {
  if (!viss2[a] || !viss2[b])
    return;
  if ((a = fnd2(a)) == (b = fnd2(b)))
    return;
  if (pars2[a] > pars2[b])
    swap(a, b);
  pars2[a] += pars2[b];
  pars2[b] = a;
}

void uni3(I a, I b) {
  if (!viss3[a] || !viss3[b])
    return;
  if ((a = fnd3(a)) == (b = fnd3(b)))
    return;
  if (pars3[a] > pars3[b])
    swap(a, b);
  pars3[a] += pars3[b];
  pars3[b] = a;
  hols[a] += hols[b];
}

I ind1(I i, I j) {
  return bnd(i, j) ? cps(i, j) : n * n;
}

void joi1(I i, I j, I k, I l) {
  uni1(ind1(i, j), ind1(k, l));
}

void joi2(I i, I j, I k, I l) {
  if (!bnd(i, j) || !bnd(k, l))
    return;
  uni2(cps(i, j), cps(k, l));
}

void joi3(I i, I j, I k, I l) {
  if (!bnd(i, j) || !bnd(k, l))
    return;
  uni3(cps(i, j), cps(k, l));
}

I siz2(I x) {
  return -pars2[fnd2(x)];
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("valleys.in", "r", stdin);
  freopen("valleys.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      cin >> cels[i][j];
  fill_n(pars1, n * n + 1, -1);
  fill_n(pars2, n * n, -1);
  fill_n(pars3, n * n, -1);
  viss1[n * n] = true;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      vals[cps(i, j)] = {cels[i][j], i, j};
  sort(vals, vals + n * n);
  for (I i = n * n - 1; i >= 0; i--) {
    const auto [cel, j, k] = vals[i];
    const I pre = cnt1;
    const I ind = cps(j, k);
    viss1[ind] = true;
    cnt1++;
    joi1(j, k, j - 1, k - 1);
    joi1(j, k, j - 1, k    );
    joi1(j, k, j - 1, k + 1);
    joi1(j, k, j    , k - 1);
    joi1(j, k, j    , k    );
    joi1(j, k, j    , k + 1);
    joi1(j, k, j + 1, k - 1);
    joi1(j, k, j + 1, k    );
    joi1(j, k, j + 1, k + 1);
    nets[i] = pre - cnt1;
  }
  for (I i = 0; i < n * n; i++) {
    const auto [cel, j, k] = vals[i];
    const I ind = cps(j, k);
    viss2[ind] = true;
    joi2(j, k, j - 1, k);
    joi2(j, k, j + 1, k);
    joi2(j, k, j, k - 1);
    joi2(j, k, j, k + 1);
    sizs[i] = siz2(ind);
  }
  Lli res = 0;
  for (I i = 0; i < n * n; i++) {
    const auto [cel, j, k] = vals[i];
    const I ind = cps(j, k);
    viss3[ind] = true;
    joi3(j, k, j - 1, k);
    joi3(j, k, j + 1, k);
    joi3(j, k, j, k - 1);
    joi3(j, k, j, k + 1);
    const I par = fnd3(ind);
    hols[par] += nets[i];
    if (hols[par] == 0)
      res += sizs[i];
  }
  printf("%lli\n", res);
  return 0;
}