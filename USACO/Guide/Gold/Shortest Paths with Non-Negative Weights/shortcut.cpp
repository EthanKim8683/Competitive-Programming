#include <iostream>
#include <cstdio>
#include <tuple>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const Lli MAX = 1e9 + 7;
const I N = 10000;

vector<pair<I, I>> a_adjs[N];
vector<I> b_adjs[N];
I c_arr[N];
I pars[N];
Lli dsts[N];
priority_queue<tuple<Lli, I, I>, vector<tuple<Lli, I, I>>, greater<tuple<Lli, I, I>>> que;
I tim_begs[N];
I tim_ends[N];
I tim = 0;

void dfs(I a) {
  tim_begs[a] = tim++;
  for (const auto b : b_adjs[a])
    dfs(b);
  tim_ends[a] = tim++;
}

B is_anc(I a, I b) {
  return tim_begs[a] <= tim_begs[b] && tim_ends[a] >= tim_ends[b];
}

I main(void) {
  freopen("shortcut.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("shortcut.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, t;
  cin >> n >> m >> t;
  fill_n(dsts, n, MAX);
  fill_n(pars, n, MAX);
  for (I i = 0; i < n; i++)
    cin >> c_arr[i];
  for (I i = 0; i < m; i++) {
    I a, b, t;
    cin >> a >> b >> t;
    a--;
    b--;
    a_adjs[a].push_back({b, t});
    a_adjs[b].push_back({a, t});
  }
  que.push({dsts[0] = 0, pars[0] = -1, 0});
  while (!que.empty()) {
    const auto [dst, par, a] = que.top();
    que.pop();
    if (dst == dsts[a] && par == pars[a]) {
      if (par != -1)
        b_adjs[par].push_back(a);
      for (const auto [b, t] : a_adjs[a])
        if (dst + t < dsts[b] || dst + t == dsts[b] && a < pars[b])
          que.push({dsts[b] = dst + t, pars[b] = a, b});
    }
  }
  dfs(0);
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    const Lli red = dsts[i] - t;
    if (red > 0) {
      Lli tot = 0;
      for (I j = 0; j < n; j++)
        if (is_anc(i, j))
          tot += c_arr[j] * red;
      res = max(res, tot);
    }
  }
  printf("%lli\n", res);
  return 0;
}