#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;
const I K = 10;

// 1. current node
// 2. subtree size
// 3. x = root, x != root
Lli dp[N][K + 1][2];
vector<I> adjs[N];
I k;

void dfs(I a, I p = -1) {
  fill(&dp[a][0][0], &dp[a][0][0] + sizeof(dp[a]) / sizeof(Lli), 0);
  dp[a][1][0] = 1;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      for (I i = 1; i <= k; i++) {
        for (I j = k; j >= 1; j--)
          if (i + j <= k)
            dp[a][i + j][0] += dp[a][j][0] * dp[b][i][0];
        dp[a][i][1] += dp[b][i][0] + dp[b][i][1];
      }
    }
  }
}

Lli slv() {
  dfs(0);
  Lli res = 0;
  for (I i = 1; i <= k; i++)
    res += dp[0][i][0] + dp[0][i][1];
  return res;
}

I main(void) {
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
  printf("%lli\n", slv());
  return 0;
}