#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<tuple<int, int, int>> edges(M);
  for (auto &[w, u, v] : edges) {
    cin >> u >> v >> w;
    u--, v--;
  }
  sort(edges.begin(), edges.end());

  vector<vector<pair<int, int>>> adj(N);
  for (auto [w, u, v] : edges) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  auto chmin = [&](int &a, int b) -> void { a = min(a, b); };

  vector<int> dsu(N, -1);
  auto leader = [&](int a) -> int {
    auto dfs = [&](auto self, int b) -> int {
      if (dsu[b] < 0) return b;
      return dsu[b] = self(self, dsu[b]);
    };
    return dfs(dfs, a);
  };

  int dist = INF;
  for (auto [w, u, v] : edges) {
    if (u == 0 and v == N - 1) {
      chmin(dist, w);
    }
    if (u == N - 1 and v == 0) {
      chmin(dist, w);
    }
  }
  int ans = dist;

  auto merge = [&](int a, int b) -> void {
    if ((a = leader(a)) == (b = leader(b))) return;

    if (dsu[b] < dsu[a]) {
      swap(a, b);
    }
    if (b == leader(N - 1)) {
      swap(a, b);
    }
    if (b == leader(0)) {
      swap(a, b);
    }

    dsu[a] += dsu[b];
    dsu[b] = a;

    for (auto [c, w] : adj[b]) {
      adj[a].push_back({c, w});

      c = leader(c);
      if (a == leader(0) and c == leader(N - 1)) {
        chmin(dist, w);
      }
      if (a == leader(N - 1) and c == leader(0)) {
        chmin(dist, w);
      }
    }
    adj[b].clear();
    adj[b].shrink_to_fit();
  };

  for (auto [w, u, v] : edges) {
    merge(u, v);

    if (leader(0) == leader(N - 1)) break;
    if (dist != INF) {
      chmin(ans, w + dist);
    }
  }
  cout << ans;
}