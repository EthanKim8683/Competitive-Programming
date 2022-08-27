#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 1e5;
const Lli MOD = 1e9 + 7;

vector<I> adjs[N];
vector<I> tops;
I inds[N];
Lli dp[N];
B viss[N];

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
  freopen("game.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
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
  dp[inds[0]] = 1;
  for (I i = 0; i < n; i++)
    for (const auto b : adjs[tops[i]])
      dp[inds[b]] = (dp[inds[b]] + dp[i]) % MOD;
  printf("%lli\n", dp[inds[n - 1]]);
  return 0;
}