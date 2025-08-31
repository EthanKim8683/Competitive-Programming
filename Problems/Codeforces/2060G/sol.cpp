#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<int> B(N);
    for (auto &e : B) cin >> e;

    vector<pair<int, int>> pairs;
    for (int i = 0; i < N; i++) {
      pairs.push_back({A[i], B[i]});
    }
    sort(pairs.begin(), pairs.end(), [&](auto a, auto b) {
      auto key = [&](auto x) -> int { return min(x.first, x.second); };
      return key(a) < key(b);
    });

    vector dp(N + 1, vector(2, vector<char>(2, false)));
    dp[1][0][0] = dp[1][1][1] = true;
    for (int i = 1; i < N; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          for (int l = 0; l < 2; l++) {
            auto [A1, B1] = pairs[i - 1];
            auto [A2, B2] = pairs[i];
            if (j) swap(A1, B1);
            if (l) swap(A2, B2);
            if (A2 > A1 and B2 > B1) {
              dp[i + 1][l][(k + l) % 2] |= dp[i][j][k];
            }
          }
        }
      }
    }
    cout << (dp[N][0][0] or dp[N][1][0] ? "YES" : "NO") << '\n';
  }
}
