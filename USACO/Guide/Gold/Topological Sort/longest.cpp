#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

vector<I> adjs[N];
vector<I> tops;
B viss[N];
I inds[N];
I dp[N];
I pars[N];
I ress[N];

void dfs(I a) {
  if (!viss[a]) {
    viss[a] = true;
    for (const auto b : adjs[a])
      dfs(b);
    tops.push_back(a);
  }
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("longest.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  fill_n(dp, n, 1);
  fill_n(pars, n, -1);
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    adjs[a - 1].push_back(b - 1);
  }
  for (I i = 0; i < n; i++)
    dfs(i);
  reverse(tops.begin(), tops.end());
  for (I i = 0; i < n; i++)
    inds[tops[i]] = i;
  pars[inds[0]] = 0;
  for (I i = 0; i < n; i++) {
    if (pars[i] != -1) {
      for (const auto b : adjs[tops[i]]) {
        const auto j = inds[b];
        if (dp[i] + 1 > dp[j]) {
          dp[j] = dp[i] + 1;
          pars[j] = i;
        }
      }
    }
  }
  if (pars[inds[n - 1]] == -1)
    printf("IMPOSSIBLE\n");
  else {
    I cur = inds[n - 1];
    I cnt = dp[cur];
    printf("%i\n", cnt);
    for (I i = cnt - 1; i >= 0; i--) {
      ress[i] = tops[cur];
      cur = pars[cur];
    }
    for (I i = 0; i < cnt; i++)
      printf("%i ", ress[i] + 1);
  }
  return 0;
}