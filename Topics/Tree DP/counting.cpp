#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 50000;
const I K = 100;
const Lli MOD = 1e9 + 7;

vector<I> adjs[N];
I a_arr[N];
Lli dp[N][K + 1][2];
I k;

void dfs(I a, I p = -1) {
  dp[a][a_arr[a]][1] = 1;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      for (I i = k; i >= 0; i--)
        for (I j = k - i; j >= 0; j--)
          (dp[a][i + j][1] += dp[a][i][1] * dp[b][j][1]) %= MOD;
      for (I i = 0; i <= k; i++)
        (dp[a][i][0] += dp[b][i][1] + dp[b][i][0]) %= MOD;
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n >> k;
    fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Lli), 0);
    for (I i = 0; i < n; i++)
      adjs[i].clear();
    for (I i = 0; i < n; i++)
      cin >> a_arr[i];
    for (I i = 0; i < n - 1; i++) {
      I u, v;
      cin >> u >> v;
      u--;
      v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    dfs(0);
    printf("%lli\n", (dp[0][k][0] + dp[0][k][1]) % MOD);
  }
  return 0;
}