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
    int N, C, M;
    cin >> N >> C >> M;

    vector<int> A(M);
    for (auto &e : A) cin >> e;

    vector dp(N + 1, vector(M + 1, vector<mint>(C + 1, 0)));
    dp[0][0][0] = 1;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j <= M; j++) {
        for (int k = 0; k < C; k++) {
          if (j + 1 <= M) {
            dp[i][j + 1][k + 1] += dp[i][j][k];
          }
          if (k + 1 <= j) {
            dp[i][j][k + 1] += dp[i][j][k];
          }
        }
        dp[i + 1][j][0] += dp[i][j][C];
      }
    }
    cout << dp[N][M][0].val() << '\n';
  }
}
