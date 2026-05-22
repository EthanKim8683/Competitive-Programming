#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  // vector dp(K * N, vector<mint>(1 << N, 0));
  // dp[0][0] = 1;
  // vector<mint> ans(N, 0);
  // for (int i = 0; i < K * N; i++) {
  //   for (int j = 0; j < (1 << N); j++) {
  //     int pc = __builtin_popcount(j);
  //     mint p = j >> (i % N) & 1 ? 0 : 1 - (mint) (pc - i / N) / (K - i / N);
  //     if (i + 1 < K * N) {
  //       dp[i + 1][j | 1 << (i % N)] += dp[i][j] * p;
  //       dp[i + 1][j] += dp[i][j] * (1 - p);
  //     }
  //     ans[i % N] += dp[i][j] * p;
  //   }
  // }
  // for (auto e : ans) {
  //   cout << e.val() << '\n';
  // }

  vector dp2(K, vector(N + 1, vector(N + 1, vector<mint>(N + 1, 0))));
  for (int i = 0; i < K; i++) {
    for (int j = 0; j <= N; j++) {
      dp2[i][j][0][0] = 1;
      for (int k = 0; k < N; k++) {
        for (int l = 0; l <= k; l++) {
          mint p = (mint) (j + l - i) / (K - i);
          dp2[i][j][k + 1][l] += dp2[i][j][k][l] * p;
          dp2[i][j][k + 1][l + 1] += dp2[i][j][k][l] * (1 - p);
        }
      }
    }
  }

  vector<mint> ans(N, 0);
  for (int i = 0; i < N; i++) {
    int L = i, R = N - 1 - i;
    vector dp(K, vector(L + 1, vector<mint>(R + 1, 0)));
    dp[0][0][0] = 1;
    for (int j = 0; j < K; j++) {
      for (int k = 0; k <= L; k++) {
        for (int l = 0; l <= R; l++) {
          for (int m = 0; m <= L - k; m++) {
            mint p1 = dp[j][k][l] * dp2[j][k + l][L - k][m],
                 p2 = (mint) (k + m + l - j) / (K - j);
            if (j + 1 < K) {
              for (int n = 0; n <= R - l; n++) {
                dp[j + 1][k + m][l + n] +=
                    p1 * p2 * dp2[j][k + m + l][R - l][n];
              }
            }
            ans[i] += p1 * (1 - p2);
          }
        }
      }
    }
  }
  for (auto e : ans) {
    cout << e.val() << '\n';
  }
}
