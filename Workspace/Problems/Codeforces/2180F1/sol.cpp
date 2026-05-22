#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

const int MAXN = 5000;
const int MAXM = 5000;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<mint> pows((MAXN + 1) * (MAXM + 1) + 1);
  pows[0] = 1;
  for (int i = 1; i < pows.size(); i++) {
    pows[i] = pows[i - 1] * 4;
  }

  mint inv_4 = (mint) 1 / 4;
  vector<mint> inv_pows((MAXN + 1) * (MAXM + 1) + 1);
  inv_pows[0] = 1;
  for (int i = 1; i < inv_pows.size(); i++) {
    inv_pows[i] = inv_pows[i - 1] * inv_4;
  }

  mint ans = 0;
  vector ps(MAXN + 1, vector<mint>(MAXM + 1, 0));
  vector dp(2, vector(MAXM, vector(2, vector<mint>(2, 0))));
  dp[0][0][false][false] += 36;
  dp[0][0][false][true] += 12;
  dp[0][0][true][false] += 12;
  dp[0][0][true][true] += 4;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXM; j++) {
      for (int k = 0; k < 2; k++) {
        for (int l = 0; l < 2; l++) {
          for (int m = 0; m < 4; m++) {
            bool down = !(k or m == 3), right = !(l or m == 2);
            if (!down and !right) {
              ps[i + 1][j + 1] +=
                  dp[i % 2][j][k][l] * inv_pows[4 + (i + j) * 2];
            } else if (!down) {
              if (j + 1 < MAXM) {
                dp[i % 2][j + 1][m == 1][false] += 3 * dp[i % 2][j][k][l];
                dp[i % 2][j + 1][m == 1][true] += dp[i % 2][j][k][l];
              }
            } else {
              if (i + 1 < MAXN) {
                dp[(i + 1) % 2][j][false][m == 0] += 3 * dp[i % 2][j][k][l];
                dp[(i + 1) % 2][j][true][m == 0] += dp[i % 2][j][k][l];
              }
            }
          }
          dp[i % 2][j][k][l] = 0;
        }
      }
    }
  }
  for (int i = 1; i <= MAXN; i++) {
    for (int j = 1; j <= MAXM; j++) {
      ps[i][j] += ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    cout << (ps[N][M] * pows[(N + 1) * (M + 1)]).val() << '\n';
  }
}
