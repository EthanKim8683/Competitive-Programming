#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;
const I K = 200;
const Lli MIN = -1e18;

vector<I> adjs[N];
I w_arr[N];
Lli dp[N][K + 1];
I k;

void dfs(I a, I p = -1) {
  dp[a][0] = w_arr[a];
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      for (I i = k; i >= 0; i--) {
        if (dp[a][i] != MIN) {
          if (i + 1 <= k)
            dp[a][i + 1] = max(dp[a][i + 1], dp[a][i]);
          for (I j = 1; i + j <= k; j++)
            dp[a][i + j] = max(dp[a][i + j], dp[a][i] + dp[b][j]);
          dp[a][i] += dp[b][0];
        }
      }
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Lli), MIN);
  I n;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> w_arr[i];
  for (I i = 0; i < n - 1; i++) {
    I u, v;
    cin >> u >> v;
    u--;
    v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs(0);
  Lli res = MIN;
  for (I i = 0; i <= k; i++)
    res = max(res, dp[0][i]);
  printf("%lli\n", res);
  return 0;
}