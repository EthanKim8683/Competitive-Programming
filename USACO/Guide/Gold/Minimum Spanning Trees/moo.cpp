#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const Lli MAX = 1e18;
const I N = 1e5;
const I Y = 10;

pair<I, I> cows[N];
set<pair<I, I>> x_arr[Y + 1];
priority_queue<pair<Lli, I>, vector<pair<Lli, I>>, greater<pair<Lli, I>>> que;
B viss[N];

Lli sqr(Lli i) {
  return i * i;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("moo.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x, y;
    cin >> x >> y;
    cows[i] = {x, y};
    x_arr[y].insert({x, i});
  }
  Lli res = 0;
  que.push({0, 0});
  while (!que.empty()) {
    const auto [dst, a] = que.top();
    que.pop();
    if (!viss[a]) {
      const auto [a_x, a_y] = cows[a];
      x_arr[a_y].erase({a_x, a});
      res += dst;
      viss[a] = true;
      for (I b_y = 0; b_y <= Y; b_y++) {
        if (!x_arr[b_y].empty()) {
          auto it = x_arr[b_y].upper_bound({a_x, a});
          if (it != x_arr[b_y].end()) {
            const auto [b_x, b] = *it;
            que.push({sqr(a_x - b_x) + sqr(a_y - b_y), b});
          }
          if (it-- != x_arr[b_y].begin()) {
            const auto [b_x, b] = *it;
            que.push({sqr(a_x - b_x) + sqr(a_y - b_y), b});
          }
        }
      }
    }
  }
  printf("%lli\n", res);
  return 0;
}