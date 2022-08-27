#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <vector>
#include <queue>

using namespace std;

using I = int;
using Lli = long long int;

const I MAX = 1e9;
const I SCL = 1e6;
const I N = 1000;
const I M = 1000;

vector<pair<I, I>> adjs[N];
tuple<I, I, I, I> edgs[N];
priority_queue<pair<I, I>, vector<pair<I, I>>, greater<pair<I, I>>> que;
I dsts[N];

I main(void) {
  freopen("pump.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("pump.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I a, b, c, f;
    cin >> a >> b >> c >> f;
    edgs[i] = {f, a - 1, b - 1, c};
  }
  sort(edgs, edgs + m, greater<tuple<I, I, I, I>>());
  I res = 0;
  for (I i = 0; i < m; i++) {
    const auto [f, a, b, c] = edgs[i];
    adjs[a].push_back({b, c});
    adjs[b].push_back({a, c});
    fill_n(dsts, n, MAX);
    que.push({dsts[0] = 0, 0});
    while (!que.empty()) {
      const auto [dst, a] = que.top();
      que.pop();
      if (dst == dsts[a])
        for (const auto [b, c] : adjs[a])
          if (dst + c < dsts[b])
            que.push({dsts[b] = dst + c, b});
    }
    res = max(res, f * SCL / dsts[n - 1]);
  }
  printf("%i\n", res);
  return 0;
}