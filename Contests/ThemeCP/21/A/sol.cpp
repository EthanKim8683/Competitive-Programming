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
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vector<int> counts(N + 1, 0);
    for (auto e : A) {
      counts[e]++;
    }

    auto chmin = [&](int &a, int b) -> void { a = min(a, b); };

    vector dp(N + 1, vector<int>(N + 1, INF));
    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j <= N; j++) {
        if (j - counts[i] >= 0) {
          chmin(dp[i + 1][j - counts[i]], dp[i][j]);
        }
        if (j + 1 <= N) {
          chmin(dp[i + 1][j + 1], dp[i][j] + 1);
        }
      }
    }
    cout << *min_element(dp[N].begin(), dp[N].end()) << '\n';
  }
}