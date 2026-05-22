#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // If we can partition the tree into chains, we can find Herobrine in at most
  // n operations.
  //
  // We want to partition the tree into chains in floor(n / 4) operations.
  //
  // How did I not see DP?

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector choices(N, vector<vector<int>>(3));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < 3; j++) {
        choices[i][j].resize(adj[i].size());
      }
    }

    vector dp(N, vector<int>(3));
    auto dfs1 = [&](auto self, int a, int p) -> void {
      dp[a][0] = 0;
      dp[a][1] = 0;
      dp[a][2] = 1;

      vector<pair<int, int>> deltas;
      for (int i = 0; i < adj[a].size(); i++) {
        int b = adj[a][i];
        if (b == p) continue;

        self(self, b, a);

        dp[a][0] += dp[b][2];
        choices[a][0][i] = 2;

        dp[a][1] += dp[b][2];
        choices[a][1][i] = 2;

        deltas.push_back({dp[b][1] - dp[b][2], i});

        pair<int, int> best = {INF, -1};
        for (int j = 0; j < 3; j++) {
          best = min(best, {dp[b][j], j});
        }
        auto [cost, j] = best;
        dp[a][2] += cost;
        choices[a][2][i] = j;
      }

      sort(deltas.begin(), deltas.end());
      for (int i = 0; i < deltas.size(); i++) {
        auto [delta, j] = deltas[i];
        if (delta >= 0) break;

        if (i < 2) {
          dp[a][0] += delta;
          choices[a][0][j] = 1;
        }

        if (i < 1) {
          dp[a][1] += delta;
          choices[a][1][j] = 1;
        }
      }
    };
    dfs1(dfs1, 0, -1);

    vector<bool> cut(N, false);
    vector<pair<int, int>> ans;
    auto dfs2 = [&](auto self, int a, int c, int p) -> void {
      if (c == 2) {
        cut[a] = true;
        ans.push_back({2, a});
      }

      for (int i = 0; i < adj[a].size(); i++) {
        int b = adj[a][i];
        if (b == p) continue;

        self(self, b, choices[a][c][i], a);
      }
    };
    pair<int, int> best = {INF, -1};
    for (int i = 0; i < 3; i++) {
      best = min(best, {dp[0][i], i});
    }
    auto [cost, i] = best;
    dfs2(dfs2, 0, i, -1);

    vector<vector<int>> adj_(N);
    for (int a = 0; a < N; a++) {
      for (auto b : adj[a]) {
        if (cut[a] or cut[b]) continue;
        adj_[a].push_back(b);
      }
    }

    vector<bool> seen(N, false);
    auto dfs3 = [&](auto self, int a) -> void {
      if (seen[a]) return;
      seen[a] = true;

      ans.push_back({1, a});

      for (auto b : adj_[a]) {
        self(self, b);
      }
    };
    for (int r = 0; r < N; r++) {
      if (adj_[r].size() > 1) continue;
      dfs3(dfs3, r);
    }

    cout << ans.size() << '\n';
    for (auto [t, x] : ans) {
      cout << t << ' ' << x + 1 << '\n';
    }
  }
}