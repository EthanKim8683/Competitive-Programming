#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  auto chmax = [&](i64 &a, i64 b) -> void { a = max(a, b); };

  vector dp(2, vector(K + 1, vector<i64>(2, -INF)));
  dp[0][0][0] = 0;
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= K; j++) {
      chmax(dp[i % 2][j][0], dp[i % 2][j][1]);
      if (i + 1 <= N) {
        chmax(dp[(i + 1) % 2][j][0], dp[i % 2][j][0]);
        if (j + 1 <= K) {
          chmax(dp[(i + 1) % 2][j + 1][1], dp[i % 2][j][0] + A[i]);
        }
        chmax(dp[(i + 1) % 2][j][1], dp[i % 2][j][1] + A[i]);
      }
      if (i != N) {
        dp[i % 2][j][0] = -INF;
        dp[i % 2][j][1] = -INF;
      }
    }
  }
  cout << dp[N % 2][K][0];
}