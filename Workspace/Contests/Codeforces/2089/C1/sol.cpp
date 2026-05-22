#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

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

    vector<mint> invs(L + 1);
    for (int i = 1; i <= L; i++) {
      invs[i] = (mint) 1 / i;
    }

    vector dp(L + 1, vector<mint>(N, 0));
    vector<mint> ans(N, 0);
    dp[L][0] = 1;
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

      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          dp[i - 1][(j + k + 1) % N] += dp[i][j] * P2[k];
          ans[(j + k) % N] += dp[i][j] * P2[k];
        }
      }
    }
    for (auto e : ans) {
      cout << e.val() << ' ';
    }
    cout << '\n';
  }
}
