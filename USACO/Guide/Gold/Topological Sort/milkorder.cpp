#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

vector<pair<I, I>> adjs[N];
vector<I> incs[N];
I tmps[N];
vector<I> tops;
priority_queue<I, vector<I>, greater<I>> que;
I n;

I ind(vector<I>& vec, I x) {
  return upper_bound(vec.begin(), vec.end(), x) - vec.begin();
}

void khn(I x) {
  tops.clear();
  for (I i = 0; i < n; i++)
    tmps[i] = ind(incs[i], x);
  for (I i = 0; i < n; i++)
    if (tmps[i] == 0)
      que.push(i);
  while (!que.empty()) {
    const auto a = que.top();
    que.pop();
    tops.push_back(a);
    for (const auto [b, y] : adjs[a])
      if (y <= x && --tmps[b] == 0)
        que.push(b);
  }
}

B tst(I x) {
  khn(x);
  return tops.size() == n;
}

I main(void) {
  freopen("milkorder.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("milkorder.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I c;
    cin >> c;
    I a;
    cin >> a;
    a--;
    for (I j = 1; j < c; j++) {
      I b;
      cin >> b;
      b--;
      adjs[a].push_back({b, i});
      incs[b].push_back(i);
      a = b;
    }
  }
  for (I i = 0; i < n; i++)
    sort(incs[i].begin(), incs[i].end());
  I l = 0;
  I r = m - 1;
  while (l < r) {
    const I m = l + (r - l + 1) / 2;
    if (tst(m))
      l = m;
    else
      r = m - 1;
  }
  khn(l);
  printf("%i", tops[0] + 1);
  for (I i = 1; i < n; i++)
    printf(" %i", tops[i] + 1);
  return 0;
}