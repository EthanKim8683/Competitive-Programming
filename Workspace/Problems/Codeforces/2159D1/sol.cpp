#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int K = 128;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<i64> A(N);
    for (auto &e : A) cin >> e;

    vector<i64> B = {A[N - 1]};
    for (int i = N - 2; i >= 0; i--) {
      if (A[i] < B.back()) {
        B.push_back(A[i]);
      }
    }
    reverse(B.begin(), B.end());

    vector<int> dp(K + 1, 0);
    for (int i = 0; i < K; i++) {
      for (int j = dp[i]; j < B.size(); j++) {
        i64 i2 = i + (B[j] + B[dp[i]] - 1) / B[dp[i]];
        if (i2 <= K) {
          dp[i2] = max(dp[i2], j + 1);
        }
      }
    }
    int ans = N;
    for (int i = 0; i <= K; i++) {
      if (dp[i] == B.size()) {
        ans = min(ans, i);
      }
    }
    cout << ans << '\n';
  }
}
