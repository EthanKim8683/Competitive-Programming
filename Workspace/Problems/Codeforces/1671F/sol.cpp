#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N = 12, K = 11, X = 11;
  vector dp(
      N + 1,
      vector(X + 1, vector(K + 1, vector(1 << K, vector<mint>(K + 1, 0)))));
  for (int i = 1; i <= K; i++) {
    dp[1][0][0][1 << (i - 1)][i] = 1;
  }
  dp[1][0][0][0][0] = 1;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j <= X; j++) {
      for (int k = j; k <= K; k++) {
        for (int l = 1; l < (1 << K); l++) {
          for (int m = 0; m <= K; m++) {
            for (int n = 0; n <= K; n++) {
              if (l << 1 >> n & 1) continue;
              int j2 = j + (m > n), k2 = k + __builtin_popcount(l >> n);
              if (j2 <= X and k2 <= K) {
                int l2 = l << 1 | 1 << n;
                l2 >>= __builtin_ctz(~l2) + 1;
                dp[i + 1][j2][k2][l2][n] += dp[i][j][k][l][m];
              }
            }
          }
        }
      }
    }
  }

  int N2 = 23;
  vector dp2(X + 1, vector(K + 1, vector(N2 + 1, vector<mint>(X + 1, 0))));
  dp2[0][0][0][0] = 1;
  for (int i = 0; i < X; i++) {
    for (int j = 0; j <= K; j++) {
      for (int k = 0; k <= N2; k++) {
        for (int l = 0; l + 1 <= X; l++) {
          for (int m = 1; m <= N and k + m <= N2; m++) {
            for (int n = 1; i + n <= X; n++) {
              for (int o = 0; j + o <= K; o++) {
                dp2[i + n][j + o][k + m][l + 1] +=
                    dp2[i][j][k][l] * dp[m][n][o][0][0];
              }
            }
          }
        }
      }
    }
  }

  vector<mint> inv_facts(X + 1);
  inv_facts[0] = 1;
  for (int i = 1; i <= X; i++) {
    inv_facts[i] = inv_facts[i - 1] / i;
  }

  int T;
  cin >> T;

  while (T--) {
    int N, K, X;
    cin >> N >> K >> X;

    auto binom = [&](int n, int k) -> mint {
      mint rv = inv_facts[k];
      for (int i = n - k + 1; i <= n; i++) {
        rv *= i;
      }
      return rv;
    };

    mint ans = 0;
    for (int i = 0; i <= min(N, N2); i++) {
      for (int j = 1; j <= min(i, X); j++) {
        ans += binom(N - i + j, j) * dp2[X][K][i][j];
      }
    }
    cout << ans.val() << '\n';
  }
}
