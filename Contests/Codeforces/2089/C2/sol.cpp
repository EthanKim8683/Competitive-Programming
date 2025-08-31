#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, L, K;
    cin >> N >> L >> K;

    vector<mint> invs(L + K + 1);
    for (int i = 1; i <= L + K; i++) {
      invs[i] = (mint) 1 / i;
    }

    vector dp(L + 1, vector(K + 1, vector<mint>(N, 0)));
    vector<mint> ans(N, 0);
    dp[L][0][0] = 1;
    for (int i = L; i >= 1; i--) {
      vector<mint> P(i);
      P[0] = 1;
      for (int j = 0; j + 1 < i; j++) {
        P[j + 1] = P[j] * (1 - invs[i - j]);
      }

      vector<mint> P2(N, 0);
      for (int j = 0; j < i; j++) {
        P2[j % N] += P[j] / (i - j);
      }

      for (int l = 0; l <= K; l++) {
        for (int j = 0; j < N; j++) {
          for (int k = 0; k < N; k++) {
            mint p = 1;
            for (int m = 0; l + m <= K; m++) {
              mint pm = (K - l - m) * invs[i + K - l - m];
              dp[i - 1][l + m][(j + k + m * i + 1) % N] +=
                  dp[i][l][j] * P2[k] * p * (1 - pm);
              ans[(j + k + m * i) % N] += dp[i][l][j] * P2[k] * p * (1 - pm);
              p *= pm;
            }
          }
        }
      }
    }
    for (auto e : ans) {
      cout << e.val() << ' ';
    }
    cout << '\n';
  }
}
