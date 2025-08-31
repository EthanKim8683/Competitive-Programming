#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<vector<int>> adj(N);
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // separate the tree into paths
  // - one endpoint is red
  // - one endpoint is blue
  // - the remaining nodes are green
  //
  // if non-exchanging
  // - we can't have two reds or two blues adjacent to each other
  // - greens can only be adjacent to greens

  // [0,:] - is red
  // [1,:] - is blue
  // [2,:] - is green
  // [:,0] - needs red and blue
  // [:,1] - has red, needs blue
  // [:,2] - has blue, needs red
  // [:,3] - has red and blue
  auto dfs = [&](auto self, int a, int p) -> array<array<mint, 4>, 3> {
    array<array<mint, 4>, 3> dp;
    dp[0][1] = 1;
    dp[1][2] = 1;
    dp[2][0] = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      auto dp2 = self(self, b, a);
      array<array<mint, 4>, 3> dp3;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          dp3[i][1] += dp[i][0] * dp2[j][2];
          dp3[i][2] += dp[i][0] * dp2[j][1];
          dp3[i][3] += dp[i][1] * dp2[j][2];
          dp3[i][3] += dp[i][2] * dp2[j][1];
          if (i == 0 and j == 0) continue;
          if (i == 1 and j == 1) continue;
          if (i == 2 and j != 2) continue;
          if (i != 2 and j == 2) continue;
          dp3[i][0] += dp[i][0] * dp2[j][3];
          dp3[i][1] += dp[i][1] * dp2[j][3];
          dp3[i][2] += dp[i][2] * dp2[j][3];
          dp3[i][3] += dp[i][3] * dp2[j][3];
        }
      }
      dp = dp3;
    }
    return dp;
  };
  auto dp = dfs(dfs, 0, -1);
  mint ans = 0;
  for (int i = 0; i < 3; i++) {
    ans += dp[i][3];
  }
  cout << ans.val();
}
