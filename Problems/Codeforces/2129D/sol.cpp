#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int MAXN = 100;
const int MAXS = 7;
const int INF = 1e9;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  // start: 6:55
  // thinking done: 7:06
  // target impl time: 20 min
  // initial impl done: 8:42

  // pause 7:10
  // resume 8:26

  vector binoms(MAXN + 1, vector<mint>(MAXN + 1));
  for (int i = 0; i <= MAXN; i++) {
    for (int j = 0; j <= MAXN; j++) {
      binoms[i][j] = binom<mint>(i, j);
    }
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    if (argc > 1) {
      N = 100;
    } else {
      cin >> N;
    }

    vector<int> S(N);
    if (argc > 1) {
      for (auto &e : S) {
        e = -1;
      }
    } else {
      for (auto &e : S) cin >> e;
    }

    bool ok = true;
    for (int i = 0; i < N; i++) {
      ok = ok and S[i] <= 2 * MAXS;
    }
    if (!ok) {
      cout << 0 << '\n';
      continue;
    }

    vector dp(N + 1,
              vector(N + 1, vector(MAXS + 1, vector<mint>(MAXS + 1, 0))));
    for (int i = 0; i <= N; i++) {
      dp[0][i][0][0] = 1;
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 0; j + i <= N; j++) {
        for (int k = 0; k < i; k++) {
          tuple<int, int, int> best = {INF, 0, 0};
          if (j != 0) {
            best = min(best, {k + 1, 0, 1});
          }
          if (j + i != N) {
            best = min(best, {i - k, 1, 0});
          }
          auto [d, dn, dm] = best;

          for (int m = 0; m + dm <= MAXS; m++) {
            for (int n = 0; n + dn <= MAXS; n++) {
              if (S[j + k] == -1) {
                for (int o = 0; o <= MAXS; o++) {
                  for (int p = 0; p <= MAXS; p++) {
                    dp[i][j][m + dm][n + dn] +=
                        dp[k][j][m][o] * dp[i - (k + 1)][j + (k + 1)][p][n] *
                        binoms[i - 1][k];
                  }
                }
              } else {
                for (int o = max(S[j + k] - MAXS, 0); o <= min(S[j + k], MAXS);
                     o++) {
                  dp[i][j][m + dm][n + dn] +=
                      dp[k][j][m][o] *
                      dp[i - (k + 1)][j + (k + 1)][S[j + k] - o][n] *
                      binoms[i - 1][k];
                }
              }
            }
          }
        }
      }
    }
    cout << dp[N][0][0][0].val() << '\n';
  }
}
