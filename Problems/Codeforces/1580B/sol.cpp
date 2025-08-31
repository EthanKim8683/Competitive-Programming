#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, K, P;
  cin >> N >> M >> K >> P;

  mint::set_mod(P);

  vector binoms(N, vector<mint>(N));
  for (int i = 0; i < N; i++) {
    binoms[i][0] = binoms[i][i] = 1;
    for (int j = 1; j < i; j++) {
      binoms[i][j] = binoms[i - 1][j - 1] + binoms[i - 1][j];
    }
  }

  vector dp(M, vector(K + 1, vector<mint>(N + 1, 0)));
  dp[0][0][0] = 1;
  mint fact = 1;
  for (int i = 1; i <= N; i++) {
    fact *= i;
    dp[0][1][i] = fact;
  }
  for (int i = 1; i < M; i++) {
    dp[i][0][0] += 1;
    for (int j = 0; j <= K; j++) {
      for (int k = max(2 * j - 1, 0); k <= N - max(2 * (K - j) - 1, 0); k++) {
        for (int l = 0; l <= j; l++) {
          for (int m = 0; m <= k - 1; m++) {
            dp[i][j][k] += dp[i - 1][l][m] * dp[i - 1][j - l][k - 1 - m] *
                           binoms[k - 1][m];
          }
        }
      }
    }
  }
  cout << dp[M - 1][K][N].val();
}
