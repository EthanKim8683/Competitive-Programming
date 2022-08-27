/*
ID: ethanki1
TASK: milk2
LANG: C++14
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

using I = int;
using B = bool;

const I N = 5000;

pair<I, I> rngs[N];
I pars[N];
vector<pair<I, I>> coms;

I fnd(I x) {
  if (pars[x] < 0)
    return x;
  return pars[x] = fnd(pars[x]);
}

B par(I x) {
  return pars[x] < 0;
}

void uni(I a, I b) {
  if ((a = fnd(a)) == (b = fnd(b)))
    return;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
  rngs[a].first = min(rngs[a].first, rngs[b].first);
  rngs[a].second = max(rngs[a].second, rngs[b].second);
}

B con(I a, I b) {
  return (rngs[a].second >= rngs[b].first && rngs[a].second <= rngs[b].second) ||
         (rngs[b].second >= rngs[a].first && rngs[b].second <= rngs[a].second);
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("milk2.in", "r", stdin);
  freopen("milk2.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, n, -1);
  for (I i = 0; i < n; i++) {
    I a, b;
    cin >> a >> b;
    rngs[i] = {a, b};
  }
  for (I i = 0; i < n; i++)
    for (I j = i + 1; j < n; j++)
      if (con(i, j))
        uni(i, j);
  for (I i = 0; i < n; i++)
    if (par(i))
      coms.push_back(rngs[i]);
  sort(coms.begin(), coms.end());
  I mlk = 0;
  I idl = 0;
  I lst = -1;
  for (auto it = coms.begin(); it != coms.end(); it++) {
    I beg, end;
    tie(beg, end) = *it;
    if (lst != -1)
      idl = max(idl, beg - lst);
    mlk = max(mlk, end - beg);
    lst = end;
  }
  printf("%i %i\n", mlk, idl);
  return 0;
}