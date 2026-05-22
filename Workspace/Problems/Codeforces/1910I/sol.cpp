#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K, C;
  cin >> N >> K >> C;

  string S;
  cin >> S;

  int M = S.size();

  vector dp(M + 1, vector<mint>(N / K + 1, 0));
  dp[0][0] = 1;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N / K + 1; j++) {
      int c = S[i] - 'a';
      if (j + 1 < N / K + 1) {
        dp[i][j + 1] += dp[i][j] * (C - c - 1);
      }
      dp[i + 1][j] += dp[i][j] * mint(C).pow(j) * mint(C - c).pow(N / K - j);
    }
  }
  mint ans = 0;
  for (int i = 0; i < N / K + 1; i++) {
    ans += dp[M][i] * mint(C).pow(N / K * (K - M) - i);
  }
  cout << ans.val() << '\n';
}
