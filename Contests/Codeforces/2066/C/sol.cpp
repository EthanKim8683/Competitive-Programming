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
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    // vector<mint> dp(N + 1, 0);
    // dp[0] = 3;
    // mint accum = 3;
    // for (int i = 1; i <= N; i++) {
    //   int sum = 0;
    //   for (int j = i - 1; j >= 0; j--) {
    //     sum ^= A[j];
    //     if (A[i] == sum) {
    //       dp[i] += 2 * dp[j];
    //       if (i + 1 <= N) {
    //         dp[i + 1] += 2 * dp[j];
    //       }
    //     }
    //   }
    //   if (i + 1 <= N) {
    //     accum += dp[i];
    //   }
    // }
    // cout << accum.val() << '\n';

    vector<mint> dp(N + 1, 0);
    map<int, mint> by_ps;
    by_ps[0] = 3;
    mint accum = 3;
    int ps = A[0];
    for (int i = 1; i <= N; i++) {
      dp[i] += 2 * by_ps[ps ^ A[i]];
      if (i + 1 <= N) {
        dp[i + 1] += 2 * by_ps[ps ^ A[i]];
        accum += dp[i];
      }
      by_ps[ps] += dp[i];
      ps ^= A[i];
    }
    cout << accum.val() << '\n';
  }
}
