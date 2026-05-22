#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"
#include "ethankim8683/graphs.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N), radj(N);
    vector<tuple<int, int, int>> edges(M);
    for (auto &[u, v, w] : edges) {
      cin >> u >> v >> w;
      u--, v--;
      adj[u].push_back(v);
      radj[v].push_back(u);
    }

    auto order = toposort(adj);
    vector<bool> seen(N, false);
    dsu d0(N);
    auto dfs = [&](auto self, int a, int r) -> void {
      if (seen[a]) return;
      seen[a] = true;
      d0.merge(a, r);
      for (auto b : radj[a]) {
        self(self, b, r);
      }
    };
    for (auto a : order) {
      dfs(dfs, a, a);
    }

    auto check = [&](int W) -> bool {
      dsu d = d0;
      for (auto [u, v, w] : edges) {
        if (w <= W) {
          d.merge(u, v);
        }
      }
      vector<vector<int>> adj(N);
      for (auto [u, v, w] : edges) {
        if (w > W and !d.same(u, v)) {
          u = d.leader(u);
          v = d.leader(v);
          adj[u].push_back(v);
        }
      }
      for (int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
      }
      auto order = toposort(adj);
      vector<bool> seen(N, false);
      auto dfs = [&](auto self, int a) -> void {
        if (seen[a]) return;
        seen[a] = true;
        for (auto b : adj[a]) {
          self(self, b);
        }
      };
      for (auto i : order) {
        if (d.leader(i) == i) {
          dfs(dfs, i);
          break;
        }
      }
      for (int i = 0; i < N; i++) {
        if (d.leader(i) == i and !seen[i]) {
          return false;
        }
      }
      return true;
    };
    int l = 0, r = 1e9 + 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << (l > 1e9 ? -1 : l) << '\n';
  }
}
