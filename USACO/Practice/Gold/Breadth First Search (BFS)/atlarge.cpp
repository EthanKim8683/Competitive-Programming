#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

vector<I> adjs[N];
I viss[N];
queue<pair<I, I>> que;
unordered_set<I> ress;
I frm = 1;

void dfs(I a, I p = -1) {
  I cnt = 0;
  for (const auto b : adjs[a]) {
    if (b != p) {
      cnt++;
      dfs(b, a);
    }
  }
  if (cnt == 0)
    que.push({frm++, a});
}

I main(void) {
  freopen("atlarge.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("atlarge.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  k--;
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(k);
  que.push({-1, k});
  while (!que.empty()) {
    const auto [frm, a] = que.front();
    que.pop();
    if (!viss[a]) {
      viss[a] = frm;
      for (const auto b : adjs[a])
        que.push({frm, b});
    } else if (frm == -1 && viss[a] > 0)
      ress.insert(viss[a]);
  }
  printf("%i\n", ress.size());
  return 0;
}