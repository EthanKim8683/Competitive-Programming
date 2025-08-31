#include <bits/stdc++.h>

#include "atcoder/convolution.hpp"
#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, K;
  cin >> N >> M >> K;

  i64 N_ = N - (i64) M * (K + 1);
  if (N_ < 0) {
    cout << 0;
    exit(0);
  }

  map<int, vector<mint>> dp;
  auto solve = [&](auto self, int n) -> void {
    if (dp.contains(n)) return;
    if (n == 1) {
      dp[n] = vector<mint>(N_ + 1);
      for (int i = 0; i <= N_; i++) {
        dp[n][i] = i < K ? 2 : 1;
      }
      return;
    }
    int n1 = n & (n - 1) ? n & -n : n >> 1, n2 = n - n1;
    self(self, n1);
    self(self, n2);
    dp[n] = convolution(dp[n1], dp[n2]);
    dp[n].resize(N_ + 1);
  };
  solve(solve, M);
  mint ans = 0;
  for (auto e : dp[M]) {
    ans += e;
  }
  cout << ans.val();
}
