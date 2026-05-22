#include <bits/stdc++.h>

#include "atcoder/mincostflow.hpp"

using namespace std;
using namespace atcoder;

std::vector<std::vector<int>> find_minimum_cost_minimal_chain_cover(
    const std::vector<std::vector<pair<int, int>>> &adj) {
  int n = adj.size();

  mcf_graph<int, int> g(2 + 2 * n);
  for (int i = 0; i < n; i++) {
    for (auto [j, w] : adj[i]) {
      g.add_edge(i, n + j, 1, w);
    }
  }
  for (int i = 0; i < n; i++) {
    g.add_edge(2 * n, i, 1, 0);
    g.add_edge(n + i, 2 * n + 1, 1, 0);
  }

  g.flow(2 * n, 2 * n + 1);
  vector<pair<int, int>> edges;
  for (auto e : g.edges()) {
    if (e.from == 2 * n or e.to == 2 * n + 1) continue;
    if (e.flow == e.cap) {
      edges.push_back({e.from, e.to - n});
    }
  }

  std::vector<int> next(n, -1);
  std::vector<bool> no_prev(n, true);
  for (auto [a, b] : edges) {
    next[a] = b;
    no_prev[b] = false;
  }
  std::vector<std::vector<int>> rv;
  for (int i = 0; i < n; i++) {
    if (!no_prev[i]) continue;

    rv.push_back({});
    auto dfs = [&](auto self, int a) -> void {
      rv.back().push_back(a);

      int b = next[a];
      if (b == -1) return;
      self(self, b);
    };
    dfs(dfs, i);
  }
  return rv;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int D, N;
  cin >> D >> N;

  vector<string> combos(N);
  for (auto &e : combos) cin >> e;

  // it should be the longest antichain

  vector<vector<pair<int, int>>> adj(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      bool ok = true;
      int d = 0;
      for (int k = 0; k < D; k++) {
        ok = ok and combos[i][k] <= combos[j][k];
        d += combos[i][k] != combos[j][k];
      }
      if (ok) {
        adj[i].push_back({j, d});
      }
    }
  }

  vector<int> ans;
  bool reset = false;
  for (auto r : find_minimum_cost_minimal_chain_cover(adj)) {
    if (reset) {
      ans.push_back(-1);
    }
    string p(D, '0');
    for (auto e : r) {
      string c = combos[e];
      for (int i = 0; i < D; i++) {
        if (p[i] != c[i]) {
          ans.push_back(i);
          p[i] = '1';
        }
      }
    }
    reset = true;
  }

  cout << ans.size() << '\n';
  for (auto e : ans) {
    if (e == -1) {
      cout << 'R' << ' ';
    } else {
      cout << e << ' ';
    }
  }
}
