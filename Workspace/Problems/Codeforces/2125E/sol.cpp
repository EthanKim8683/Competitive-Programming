#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // \sum_{q \in Q} max(Q) - q <= x
  // all max(Q) - q are distinct
  // n(n+1)/2 <= x+1
  //
  // A = {1, ...}

  int T;
  cin >> T;

  while (T--) {
    int N, X;
    cin >> N >> X;

    if ((i64) N * (N + 1) / 2 - 1 > X) {
      cout << 0 << '\n';
      continue;
    }

    if (N == 1) {
      cout << X << '\n';
      continue;
    }

    vector dp(N + 1, vector<i64>(X + 2, 0));
    dp[1][N] = 1;
    for (int i = 1; i < N; i++) {
      for (int j = 0; j + N - i <= X + 1; j++) {
        (dp[i + 1][j + N - i] += dp[i][j]) %= MOD;
        (dp[i + 1][j + N - i] += dp[i + 1][j]) %= MOD;
      }
    }
    i64 ans = 0;
    for (int i = 1 + 1; i <= X + 1; i++) {
      (ans += (X + 1 + 1 - i) * dp[N][i]) %= MOD;
    }
    cout << ans << '\n';
  }
}