#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;
const Lli MOD = 1e9 + 7;

// 1. current node
// 2. color 1, color 2, color 3
Lli dp[N][3];
vector<I> adjs[N];
I cols[N];

void dfs(I a, I p = -1) {
  if (cols[a] == 0)
    fill_n(dp[a], 3, 1);
  else
    dp[a][cols[a] - 1] = 1;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      (dp[a][0] *= dp[b][1] + dp[b][2]) %= MOD;
      (dp[a][1] *= dp[b][0] + dp[b][2]) %= MOD;
      (dp[a][2] *= dp[b][0] + dp[b][1]) %= MOD;
    }
  }
}

Lli slv() {
  dfs(0);
  return (dp[0][0] + dp[0][1] + dp[0][2]) % MOD;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("barnpainting.in", "r", stdin);
  freopen("barnpainting.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for (I i = 0; i < k; i++) {
    I b, c;
    cin >> b >> c;
    cols[b - 1] = c;
  }
  printf("%lli\n", slv());
  return 0;
}