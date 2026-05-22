#include <bits/stdc++.h>

#include "atcoder/modint"

using namespace std;
using namespace atcoder;
using mint = modint998244353;
using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, X;
  cin >> N >> X;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> counts(N, 0);
  int count = 0;
  for (auto e : A) {
    if (e >= N) {
      count++;
    } else {
      counts[e]++;
    }
  }

  vector dp(N + 1, vector(N + 1, vector<mint>(N * (N - 1) / 2 + 1, 0)));
  dp[N][0][0] = 1;
  for (int i = N - 1; i >= 0; i--) {
    count += counts[i];
    for (int j = 0; j < counts[i]; j++) {
      for (int k = 0; k <= N; k++) {
        for (int l = 0; l <= N * (N - 1) / 2; l++) {
          if (k - 1 >= 0 and l - i >= 0) {
            dp[i + 1][k - 1][l - i] += dp[i + 1][k][l] * k;
          }
        }
      }
    }
    for (int j = 0; j <= N; j++) {
      for (int k = 0; k <= N * (N - 1) / 2; k++) {
        if (j + 1 <= N and k + i <= N * (N - 1) / 2) {
          dp[i][j + 1][k + i] += dp[i + 1][j][k];
        }
        dp[i][j][k] += dp[i + 1][j][k] * (count - (N - (i + 1) - j));
      }
    }
  }

  mint ans = 0;
  for (int i = 0;
       i <= X + N * (N - 1) / 2 - accumulate(A.begin(), A.end(), 0ll) and
       i <= N * (N - 1) / 2;
       i++) {
    ans += dp[0][0][i];
  }
  cout << ans.val();
}