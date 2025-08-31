#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;
  mint P = mint(Q) / 10000;

  vector binoms(N + 1, vector<mint>(N + 1));
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= i; j++) {
      binoms[i][j] = binom<mint>(i, j);
    }
  }

  vector dp(N + 1, vector(N + 1, vector<mint>(2, 0)));
  dp[0][0][0] = 1;
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= i - 1; j++) {
      for (int k = 0; k < 2; k++) {
        dp[i][max(j - 1, 0)][0] += dp[i - 1][j][k] * P;
        dp[i][j + 1][0] += dp[i - 1][j][k] * (1 - P);
      }
    }
    for (int j = 1; j <= i - 1; j++) {
      mint lhs = 0, rhs = 0;
      for (int k = 0; k <= max(j, i - j); k++) {
        for (int l = 0; l < 2; l++) {
          rhs += dp[i - j][k][l];
        }
        dp[i][k][1] += dp[j][k][0] * rhs * binoms[i][j];
        for (int l = 0; l < 2; l++) {
          dp[i][k][1] += lhs * dp[i - j][k][l] * binoms[i][j];
        }
        lhs += dp[j][k][0];
      }
    }
  }
  mint total = 1;
  for (int i = 0; i < N; i++) {
    total *= 2 * i + 1;
  }
  cout << ((dp[N][0][0] + dp[N][0][1]) / total).val();
}
