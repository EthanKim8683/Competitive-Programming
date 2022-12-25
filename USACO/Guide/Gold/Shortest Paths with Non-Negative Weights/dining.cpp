#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MAX = 1e18;
const I N = 50000;

vector<pair<I, I>> adjs[N];
priority_queue<pair<Lli, I>, vector<pair<Lli, I>>, greater<pair<Lli, I>>> que;
Lli a_dsts[N];
Lli b_dsts[N];

void djk(Lli dsts[]) {
  while (!que.empty()) {
    const auto [dst, a] = que.top();
    que.pop();
    for (const auto [b, t] : adjs[a])
      if (dst + t < dsts[b])
        que.push({dsts[b] = dst + t, b});
  }
}

I main(void) {
  freopen("dining.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("dining.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, k;
  cin >> n >> m >> k;
  fill_n(a_dsts, n, MAX);
  fill_n(b_dsts, n, MAX);
  for (I i = 0; i < m; i++) {
    I a, b, t;
    cin >> a >> b >> t;
    a--;
    b--;
    adjs[a].push_back({b, t});
    adjs[b].push_back({a, t});
  }
  que.push({a_dsts[n - 1] = 0, n - 1});
  djk(a_dsts);
  for (I i = 0; i < k; i++) {
    I x, y;
    cin >> x >> y;
    x--;
    que.push({b_dsts[x] = a_dsts[x] - y, x});
  }
  djk(b_dsts);
  for (I i = 0; i < n - 1; i++)
    printf("%i\n", b_dsts[i] <= a_dsts[i]);
  return 0;
}