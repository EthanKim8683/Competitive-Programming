#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const Lli MAX = 1e18;
const I N = 1e5;

vector<pair<I, Lli>> adjs[N];
priority_queue<pair<Lli, I>, vector<pair<Lli, I>>, greater<pair<Lli, I>>> stts;
Lli dsts[N];
B viss[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("road2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  fill_n(dsts, n, MAX);
  for (I i = 0; i < m; i++) {
    I a, b;
    Lli c;
    cin >> a >> b >> c;
    a--;
    b--;
    adjs[a].push_back({b, c});
    adjs[b].push_back({a, c});
  }
  I cnt = 0;
  Lli cst = 0;
  stts.push({dsts[0] = 0, 0});
  while (!stts.empty()) {
    const auto [dst, a] = stts.top();
    stts.pop();
    if (!viss[a] && dsts[a] == dst) {
      viss[a] = true;
      cst += dst;
      cnt++;
      for (const auto [b, c] : adjs[a])
        if (c < dsts[b])
          stts.push({dsts[b] = c, b});
    }
  }
  if (cnt == n)
    printf("%lli\n", cst);
  else
    printf("IMPOSSIBLE\n");
  return 0;
}