#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 1e5;

Lli s_arr[N];
vector<pair<I, Lli>> adjs[N];
vector<I> tops;
I inds[N];
B viss[N];
Lli dp[N];

void dfs(I a) {
  if (!viss[a]) {
    viss[a] = true;
    for (const auto [b, x] : adjs[a])
      dfs(b);
    tops.push_back(a);
  }
}

I main(void) {
  freopen("timeline.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("timeline.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, c;
  cin >> n >> m >> c;
  for (I i = 0; i < n; i++)
    cin >> s_arr[i];
  for (I i = 0; i < c; i++) {
    I a, b, x;
    cin >> a >> b >> x;
    adjs[a - 1].push_back({b - 1, x});
  }
  for (I i = 0; i < n; i++)
    dfs(i);
  reverse(tops.begin(), tops.end());
  for (I i = 0; i < n; i++)
    inds[tops[i]] = i;
  for (I i = 0; i < n; i++)
    dp[inds[i]] = s_arr[i];
  for (I i = 0; i < n; i++) {
    for (const auto [b, x] : adjs[tops[i]]) {
      const auto j = inds[b];
      dp[j] = max(dp[j], dp[i] + x);
    }
  }
  for (I i = 0; i < n; i++)
    printf("%i\n", dp[inds[i]]);
  return 0;
}