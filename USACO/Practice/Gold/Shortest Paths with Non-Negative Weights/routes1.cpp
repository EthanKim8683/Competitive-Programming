#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MAX = 1e18;
const I N = 1e5;

vector<pair<I, Lli>> adjs[N];
priority_queue<pair<Lli, I>, vector<pair<Lli, I>>, greater<pair<Lli, I>>> stts;
Lli dsts[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("routes1.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  fill_n(dsts, n, MAX);
  for (I i = 0; i < m; i++) {
    I a, b;
    Lli c;
    cin >> a >> b >> c;
    adjs[a - 1].push_back({b - 1, c});
  }
  stts.push({dsts[0] = 0, 0});
  while (!stts.empty()) {
    const auto [dst, a] = stts.top();
    stts.pop();
    if (dsts[a] == dst)
      for (const auto [b, c] : adjs[a])
        if (dst + c < dsts[b])
          stts.push({dsts[b] = dst + c, b});
  }
  for (I i = 0; i < n; i++)
    printf("%lli ", dsts[i]);
  return 0;
}