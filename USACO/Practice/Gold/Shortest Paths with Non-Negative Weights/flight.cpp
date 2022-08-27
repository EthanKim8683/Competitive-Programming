#include <iostream>
#include <cstdio>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;

vector<pair<I, Lli>> adjs[N];
multiset<Lli> dsts[N];
priority_queue<pair<Lli, I>, vector<pair<Lli, I>>, greater<pair<Lli, I>>> que;

I main(void) {
#ifdef ETHANKIM8683
  freopen("flight.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, k;
  cin >> n >> m >> k;
  for (I i = 0; i < m; i++) {
    I a, b, c;
    cin >> a >> b >> c;
    adjs[a - 1].push_back({b - 1, c});
  }
  dsts[0].insert(0);
  que.push({0, 0});
  while (!que.empty()) {
    const auto [dst, a] = que.top();
    que.pop();
    if (dst <= *dsts[a].rbegin()) {
      for (const auto [b, c] : adjs[a]) {
        if (dsts[b].size() < k) {
          dsts[b].insert(dst + c);
          que.push({dst + c, b});
        } else if (dst + c < *dsts[b].rbegin()) {
          dsts[b].insert(dst + c);
          dsts[b].erase(--dsts[b].end());
          que.push({dst + c, b});
        }
      }
    }
  }
  auto it = dsts[n - 1].begin();
  for (I i = 0; i < k; i++)
    printf("%lli ", *it++);
  return 0;
}