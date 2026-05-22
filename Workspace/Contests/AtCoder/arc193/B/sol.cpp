#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  string S;
  cin >> S;

  for (auto &e : S) {
    e -= '0';
  }

  vector dp(N + 1, vector(2, vector(2, vector(2, vector<mint>(2, 0)))));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      dp[0][i][j][i][j] = 1;
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 2; j++) {              // initial carry
      for (int k = 0; k < 2; k++) {            // initial spoke in resolved?
        for (int l = 0; l < 2; l++) {          // carry
          for (int m = 0; m < 2; m++) {        // spoke in resolved?
            for (int n = 0; n <= S[i]; n++) {  // spoke out or in?
              for (int o = 0; o <= 1; o++) {   // carry out or in?
                int m_ = !n and (m or !l);
                if (n < S[i] and !m_) continue;
                dp[i + 1][j][k][!o][m_] += dp[i][j][k][l][m];
              }
            }
          }
        }
      }
    }
  }
  mint ans = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ans += dp[N][i][j][i][j];
    }
  }
  ans -= 2;  // ?
  cout << ans.val();
}
