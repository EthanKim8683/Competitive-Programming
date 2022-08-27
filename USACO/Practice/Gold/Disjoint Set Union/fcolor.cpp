#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;

I pars[N];
I inds[N];
B viss[N];
I cols[N][2];
vector<I> adjs[N];

I fnd(I x) {
  if (pars[x] < 0)
    return x;
  return pars[x] = fnd(pars[x]);
}

void uni(I& a, I& b) {
  if (a == -1) {
    a = b;
    return;
  }
  if (b == -1) {
    b = a;
    return;
  }
  if ((a = fnd(a)) == (b = fnd(b)))
    return;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
  uni(cols[a][1], cols[b][1]);
}

void dfs(I a) {
  if (viss[a])
    return;
  viss[a] = true;
  for (const auto b : adjs[a]) {
    uni(cols[fnd(a)][1], cols[fnd(b)][0]);
    dfs(b);
  }
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("fcolor.in", "r", stdin);
  freopen("fcolor.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    adjs[a - 1].push_back(b - 1);
  }
  fill_n(pars, n, -1);
  fill_n(inds, n, -1);
  for (I i = 0; i < n; i++) {
    cols[i][0] = i;
    cols[i][1] = -1;
  }
  for (I i = 0; i < n; i++)
    dfs(i);
  I ind = 1;
  for (I i = 0; i < n; i++) {
    const I par = fnd(i);
    if (inds[par] == -1)
      inds[par] = ind++;
    printf("%i\n", inds[par]);
  }
  return 0;
}