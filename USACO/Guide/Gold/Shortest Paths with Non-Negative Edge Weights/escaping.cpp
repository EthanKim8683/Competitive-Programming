#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MAX = 1e18;
const I N = 1e5;
const I M = 1e5;
const I K = 1e5;
const I H = 1e6;

I x_arr[N];
vector<I> pnts[N];
priority_queue<pair<Lli, I>, vector<pair<Lli, I>>, greater<pair<Lli, I>>> que;
unordered_map<Lli, I> crds; 
vector<pair<I, Lli>> adjs[2 * K + 2];
Lli dsts[2 * K + 2];
I cnt = 0;

I cps(I r, I c) {
  const Lli crd = (Lli) r * M + c;
  const auto it = crds.find(crd);
  if (it == crds.end()) {
    crds.insert({crd, cnt});
    return cnt++;
  }
  return it->second;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("escaping.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, m, k;
    cin >> n >> m >> k;
    fill_n(dsts, 2 * k + 2, MAX);
    crds.clear();
    for (I i = 0; i < n; i++)
      pnts[i].clear();
    for (I i = 0; i < 2 * k + 2; i++)
      adjs[i].clear();
    cnt = 0;
    for (I i = 0; i < n; i++)
      cin >> x_arr[i];
    for (I i = 0; i < k; i++) {
      I a, b, c, d, h;
      cin >> a >> b >> c >> d >> h;
      pnts[--a].push_back(--b);
      pnts[--c].push_back(--d);
      adjs[cps(a, b)].push_back({cps(c, d), (Lli) H * (c - a) - h});
    }
    pnts[0].push_back(0);
    pnts[n - 1].push_back(m - 1);
    for (I i = 0; i < n; i++) {
      if (!pnts[i].empty()) {
        sort(pnts[i].begin(), pnts[i].end());
        I a = pnts[i][0];
        for (I j = 1; j < pnts[i].size(); j++) {
          const I b = pnts[i][j];
          adjs[cps(i, a)].push_back({cps(i, b), (Lli) x_arr[i] * abs(a - b)});
          adjs[cps(i, b)].push_back({cps(i, a), (Lli) x_arr[i] * abs(a - b)});
          a = b;
        }
      }
    }
    que.push({dsts[cps(0, 0)] = 0, cps(0, 0)});
    while (!que.empty()) {
      const auto [dst, a] = que.top();
      que.pop();
      if (dst == dsts[a])
        for (const auto [b, d] : adjs[a])
          if (dst + d < dsts[b])
            que.push({dsts[b] = dst + d, b});
    }
    const auto res = dsts[cps(n - 1, m - 1)];
    if (res == MAX)
      printf("NO ESCAPE\n");
    else
      printf("%lli\n", res - (Lli) H * (n - 1));
  }
  return 0;
}