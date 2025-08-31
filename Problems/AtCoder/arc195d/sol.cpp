#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    auto chmin = [&](int &a, int b) -> void { a = min(a, b); };
    vector dp(N + 1, vector<int>(2, INF));
    dp[1][false] = 1;
    dp[1][true] = 2;
    for (int i = 1; i < N; i++) {
      for (int j = 0; j < 2; j++) {
        int pv = A[i - 1];
        if (j) {
          if (i - 2 < 0) continue;
          pv = A[i - 2];
        }
        if (i + 2 <= N) {
          int v = A[i + 1];
          chmin(dp[i + 2][true], dp[i][j] + 1 + (pv != v) + (A[i] != A[i + 1]));
        }
        int v = A[i];
        chmin(dp[i + 1][false], dp[i][j] + (pv != v));
      }
    }
    cout << dp[N][false] << '\n';
  }
}
