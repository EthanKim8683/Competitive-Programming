#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100000;
const Lli MAX = 1e18;

vector<pair<I, I>> adjs[N];
priority_queue<pair<Lli, I>, vector<pair<Lli, I>>, greater<pair<Lli, I>>> que;
Lli diss1[N];
Lli diss2[N];
Lli diss3[N];
Lli mins1[N];
Lli mins2[N];
Lli tots[N];

void cmb(Lli& a, Lli b) {
  a = min(a, b);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  I s, t;
  cin >> s >> t;
  s--;
  t--;
  I u, v;
  cin >> u >> v;
  u--;
  v--;
  for (I i = 0; i < m; i++) {
    I a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    adjs[a].push_back({b, c});
    adjs[b].push_back({a, c});
  }
  fill_n(diss1, n, MAX);
  fill_n(diss2, n, MAX);
  fill_n(diss3, n, MAX);
  que.push({diss1[u] = 0, u});
  while (!que.empty()) {
    const auto [dis, a] = que.top();
    que.pop();
    if (dis != diss1[a])
      continue;
    for (const auto [b, c] : adjs[a])
      if (dis + c < diss1[b])
        que.push({diss1[b] = dis + c, b});
  }
  que.push({diss2[v] = 0, v});
  while (!que.empty()) {
    const auto [dis, a] = que.top();
    que.pop();
    if (dis != diss2[a])
      continue;
    for (const auto [b, c] : adjs[a])
      if (dis + c < diss2[b])
        que.push({diss2[b] = dis + c, b});
  }
  for (I i = 0; i < n; i++)
    tots[i] = diss1[i] + diss2[i];
  copy_n(diss1, n, mins1);
  copy_n(diss2, n, mins2);
  que.push({diss3[s] = 0, s});
  while (!que.empty()) {
    const auto [dis, a] = que.top();
    que.pop();
    if (dis != diss3[a])
      continue;
    for (const auto [b, c] : adjs[a]) {
      if (dis + c < diss3[b]) {
        tots[b] = min(tots[a], diss1[b] + diss2[b]);
        cmb(tots[b], mins1[a] + diss2[b]);
        cmb(tots[b], mins2[a] + diss1[b]);
        mins1[b] = min(mins1[a], diss1[b]);
        mins2[b] = min(mins2[a], diss2[b]);
        que.push({diss3[b] = dis + c, b});
      } else if (dis + c == diss3[b]) {
        cmb(tots[b], tots[a]);
        cmb(tots[b], mins1[a] + diss2[b]);
        cmb(tots[b], mins2[a] + diss1[b]);
        cmb(mins1[b], mins1[a]);
        cmb(mins2[b], mins2[a]);
      }
    }
  }
  printf("%lli\n", min(tots[t], diss2[u]));
  return 0;
}