#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 3e5;

vector<pair<I, I>> adjs[N];
vector<I> p_arr;
priority_queue<tuple<I, I, I>, vector<tuple<I, I, I>>, greater<tuple<I, I, I>>> que;
vector<I> ress;
B viss[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("796d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k, d;
  cin >> n >> k >> d;
  for (I i = 0; i < k; i++) {
    I p;
    cin >> p;
    p_arr.push_back(p - 1);
  }
  sort(p_arr.begin(), p_arr.end());
  p_arr.erase(unique(p_arr.begin(), p_arr.end()), p_arr.end());
  for (const auto p : p_arr)
    que.push({0, p, 0});
  for (I i = 1; i <= n - 1; i++) {
    I u, v;
    cin >> u >> v;
    u--;
    v--;
    adjs[u].push_back({v, i});
    adjs[v].push_back({u, i});
  }
  while (!que.empty()) {
    const auto [dst, a, i] = que.top();
    que.pop();
    if (!viss[a]) {
      viss[a] = true;
      for (const auto [b, j] : adjs[a])
        if (j != i)
          que.push({dst + 1, b, j});
    } else
      ress.push_back(i);
  }
  sort(ress.begin(), ress.end());
  ress.erase(unique(ress.begin(), ress.end()), ress.end());
  printf("%i\n", ress.size());
  for (const auto res : ress)
    printf("%i ", res);
  return 0;
}