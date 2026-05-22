#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 6e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<i64> A(N);
    for (auto &e : A) cin >> e;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int x, y;
      cin >> x >> y;
      x--, y--;
      adj[x].push_back(y);
      adj[y].push_back(x);
    }

    int logN = __lg(N) + 3;

    vector dp(N, vector<i64>(logN, INF));
    auto dfs = [&](auto self, int a, int p) -> void {
      for (int i = 0; i < logN; i++) {
        dp[a][i] = (i + 1) * A[a];
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);

        auto dp0 = dp[a];
        fill(dp[a].begin(), dp[a].end(), INF);
        for (int i = 0; i < logN; i++) {
          for (int j = 0; j < logN; j++) {
            if (i == j) continue;
            dp[a][i] = min(dp[a][i], dp0[i] + dp[b][j]);
          }
        }
      }
    };
    dfs(dfs, 0, -1);

    cout << *min_element(dp[0].begin(), dp[0].end()) << '\n';
  }
}
