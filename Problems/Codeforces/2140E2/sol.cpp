#include <bits/stdc++.h>

#include "atcoder/modint"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    int K;
    cin >> K;

    vector<int> C(K);
    for (auto &e : C) {
      cin >> e;
      e--;
    }

    vector<bool> good(N, false);
    for (auto e : C) {
      good[e] = true;
    }

    vector dp(N + 1, vector<bool>(1 << N, false));
    dp[1][(N - 1) % 2 == 0 ? 1 : 0] = true;
    for (int i = 2; i <= N; i++) {
      for (int j = 0; j < (1 << i); j++) {
        for (int k = 0; k < i; k++) {
          if (!good[k]) continue;
          dp[i][j] =
              dp[i][j] or !dp[i - 1][j ^ (j >> k << k) ^ (j >> (k + 1) << k)];
        }
      }
    }

    vector<int> counts(N + 1, 0);
    for (int i = 0; i < (1 << N); i++) {
      if (!dp[N][i]) continue;
      counts[__builtin_popcount(i)]++;
    }

    mint ans = 0;
    for (int i = 1; i <= M; i++) {
      mint count = 0;
      for (int j = 0; j <= N; j++) {
        count += counts[j] * mint(i - 1).pow(N - j) * mint(M + 1 - i).pow(j);
        count -= counts[j] * mint(i).pow(N - j) * mint(M - i).pow(j);
      }
      ans += i * count;
    }
    cout << ans.val() << '\n';
  }
}
