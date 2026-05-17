#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // Marat can be "chased away" by a pair of enemies
  //
  // for each node, between each time its visited by enemies, find the earliest
  // moment we could visit it

  int T;
  cin >> T;

  while (T--) {
    int N, M, X, Y;
    cin >> N >> M >> X >> Y;
    X--, Y--;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int v, u;
      cin >> v >> u;
      v--, u--;
      adj[v].push_back(u);
      adj[u].push_back(v);
    }

    vector<pair<int, int>> enemies(M);
    for (auto &[a, b] : enemies) {
      cin >> a >> b;
      a--, b--;
    }

    vector<vector<int>> visits(N);
    auto dfs = [&](auto self, int a, int t, int d, int p) -> bool {
      bool found = a == t;
      for (auto b : adj[a]) {
        if (b == p) continue;
        found = found or self(self, b, t, d + 1, a);
      }
      if (found) {
        visits[a].push_back(d);
      }
      return found;
    };
    for (auto [a, b] : enemies) {
      dfs(dfs, a, b, 1, -1);
    }
    for (auto &r : visits) {
      sort(r.begin(), r.end());
    }

    vector<vector<pair<int, int>>> ranges(N);
    for (int i = 0; i < N; i++) {
      int l = 1;
      for (auto e : visits[i]) {
        if (l < e) {
          ranges[i].emplace_back(l, e);
        }
        l = e + 1;
      }
      ranges[i].emplace_back(l, INF);
    }

    int ans = -1;
    vector<vector<bool>> seen(N);
    for (int i = 0; i < N; i++) {
      seen[i].resize(ranges[i].size(), false);
    }
    vector<int> index(N, -1), dmax(N, 0);
    vector<vector<pair<int, int>>> queue(2 * N + 2);
    auto explore = [&](int a, int d) -> void {
      if (a == Y) {
        ans = d;
      }

      auto [d1, d2] = ranges[a][index[a]];
      for (auto b : adj[a]) {
        queue[d + 1].emplace_back(b, d2 + 1);
      }
    };
    auto check = [&](int a, int d) -> void {
      if (index[a] == -1) return;
      if (index[a] >= ranges[a].size()) return;

      auto [d1, d2] = ranges[a][index[a]];
      if (dmax[a] <= d1) return;
      if (d2 <= d) return;

      if (seen[a][index[a]]) return;
      seen[a][index[a]] = true;

      explore(a, d);
    };
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < ranges[i].size(); j++) {
        auto [d1, d2] = ranges[i][j];
        queue[d1].emplace_back(i, -1);
      }
    }
    dmax[X] = 2;
    for (int i = 1; i <= 2 * N; i++) {
      for (auto [a, d] : queue[i]) {
        if (d < 0) {
          index[a]++;
          check(a, i);
        } else {
          dmax[a] = max(dmax[a], d);
          check(a, i);
        }
      }
      queue[i].clear();
      if (ans != -1) break;
    }
    cout << ans << '\n';
  }
}
