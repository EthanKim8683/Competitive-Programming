#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector A(2, vector<int>(N));
    for (auto &r : A) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    auto get_range = [&](int x) -> pair<int, int> {
      if (x == -1) {
        return {1, K};
      } else {
        return {x, x};
      }
    };

    vector dp(N, vector<mint>(K + 2, 0));
    vector<mint> dp2(N, 0);
    {
      auto [l, r] = get_range(A[0][0]);
      dp2[0] = r - l + 1;
    }
    for (int i = 0; i + 1 < N; i++) {
      auto [l1, r1] = get_range(A[1][i]);
      auto [l2, r2] = get_range(A[0][i + 1]);

      auto add_range = [&](int l, int r, mint x) -> void {
        l = clamp(l, 0, K + 1);
        r = clamp(r, 0, K + 1);
        r = max(r, l);
        dp[i + 1][l] += x;
        dp[i + 1][r] -= x;
      };
      auto add_range2 = [&](int l, int r, mint x) -> void {
        r = max(r, l);
        dp2[i + 1] += dp2[i] * (r - l);
      };

      for (int j = l1; j <= r1; j++) {
        // for (int l = l2; l <= min(r2, j - 1); l++) {
        //   dp[i + 1][j - l] += dp2[i];
        // }
        add_range(j - min(r2, j - 1), j - l2 + 1, dp2[i]);
        // for (int l = max(l2, j); l <= r2; l++) {
        //   dp2[i + 1] += dp2[i];
        // }
        add_range2(max(l2, j), r2 + 1, dp2[i]);
        for (int k = 0; k <= K; k++) {
          // for (int l = l2; l <= min(r2, j - 1); l++) {
          //   dp[i + 1][j - l] += dp[i][k];
          // }
          add_range(j - min(r2, j - 1), j - l2 + 1, dp[i][k]);
          // for (int l = max(l2, j); l <= min(r2, k + j); l++) {
          //   dp[i + 1][k + j - l] += dp[i][k];
          // }
          add_range(k + j - min(r2, k + j), k + j - max(l2, j) + 1, dp[i][k]);
        }
      }

      for (int j = 0; j <= K; j++) {
        dp[i + 1][j + 1] += dp[i + 1][j];
      }
    }
    mint sum = dp2[N - 1];
    for (auto e : dp[N - 1]) {
      sum += e;
    }
    mint ans;
    {
      auto [l, r] = get_range(A[1][N - 1]);
      ans = sum * (r - l + 1);
    }
    cout << ans.val() << '\n';
  }
}
