#include <bits/stdc++.h>

#include "atcoder/convolution.hpp"
#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<vector<int>> adj(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> ch(N, 0);
  auto dfs = [&](auto self, int a, int p) -> void {
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a);
      ch[a]++;
    }
  };
  dfs(dfs, 0, -1);

  // vector dp(N + 1, vector<mint>(N + 1, 0));
  // dp[0][0] = 1;
  // for (int i = 0; i < N; i++) {
  //   for (int j = 0; j <= i; j++) {
  //     dp[i + 1][j + 1] += dp[i][j] * ch[i];
  //     dp[i + 1][j] += dp[i][j];
  //   }
  // }
  // mint ans = 0;
  // for (int i = 0; i <= N; i++) {
  //   ans += dp[N][i] * fact<mint>(N - i) * (i % 2 == 0 ? 1 : -1);
  // }
  // cout << ans.val();

  auto dnc = [&](auto self, int l, int r) -> vector<mint> {
    if (r - l == 1) return {1, ch[l]};

    int m = l + (r - l) / 2;
    return convolution(self(self, l, m), self(self, m, r));
  };
  auto dp = dnc(dnc, 0, N);
  mint ans = 0;
  for (int i = 0; i <= N; i++) {
    ans += dp[i] * fact<mint>(N - i) * (i % 2 == 0 ? 1 : -1);
  }
  cout << ans.val();
}
