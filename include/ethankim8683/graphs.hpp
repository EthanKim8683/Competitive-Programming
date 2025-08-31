#ifndef ETHANKIM8683_GRAPHS
#define ETHANKIM8683_GRAPHS

#include <assert.h>

#include <algorithm>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>

std::vector<int> toposort(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<bool> seen(n, false);
  std::vector<int> rv;
  auto dfs = [&](auto self, int a) -> void {
    if (seen[a]) return;
    seen[a] = true;

    for (auto b : adj[a]) {
      self(self, b);
    }
    rv.push_back(a);
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  reverse(rv.begin(), rv.end());
  return rv;
}

std::vector<int> toposort(const std::vector<std::vector<int>> &adj,
                          const std::function<bool(int, int)> &cmp) {
  int n = adj.size();

  std::vector<int> deg(n, 0);
  for (auto adja : adj) {
    for (auto b : adja) {
      deg[b]++;
    }
  }

  auto rcmp = [&](int a, int b) -> bool { return cmp(b, a); };
  std::priority_queue<int, std::vector<int>, decltype(rcmp)> pq(rcmp);
  auto nudge = [&](int a) -> void {
    if (deg[a] != 0) return;
    pq.push(a);
  };
  for (int i = 0; i < n; i++) {
    nudge(i);
  }
  std::vector<int> rv;
  while (pq.size() > 0) {
    int a = pq.top();
    pq.pop();
    rv.push_back(a);
    for (auto b : adj[a]) {
      if (deg[b] == 0) continue;
      deg[b]--;
      nudge(b);
    }
  }
  return rv;
}

bool is_acyclic(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  auto order = toposort(adj);
  std::vector<bool> seen(n, false);
  for (auto a : order) {
    seen[a] = true;
    for (auto b : adj[a]) {
      if (seen[b]) return false;
    }
  }
  return true;
}

// Finds any minimal chain cover provided edges of a maximal bipartite matching
std::vector<std::vector<int>> find_minimal_chain_cover(
    const std::vector<std::pair<int, int>> &edges) {
  int n = 0;
  for (auto [a, b] : edges) {
    n = std::max(n, a + 1);
    n = std::max(n, b + 1);
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

// https://cp-algorithms.com/graph/bridge-searching.html
std::vector<std::pair<int, int>> find_bridges(
    const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<bool> seen(n, false);
  std::vector<int> tin(n), tmin(n);
  std::vector<std::pair<int, int>> rv;
  int t = 0;
  auto dfs = [&](auto self, int a, int p) -> void {
    seen[a] = true;
    tin[a] = tmin[a] = t++;
    bool skipped = false;
    for (auto b : adj[a]) {
      if (b == p and !skipped) {
        skipped = true;
        continue;
      }
      if (seen[b]) {
        tmin[a] = std::min(tmin[a], tin[b]);
      } else {
        self(self, b, a);
        tmin[a] = std::min(tmin[a], tmin[b]);
        if (tmin[b] > tin[a]) {
          int u = a, v = b;
          if (u > v) {
            std::swap(u, v);
          }
          rv.push_back({u, v});
        }
      }
    }
  };
  for (int i = 0; i < n; i++) {
    if (seen[i]) continue;
    dfs(dfs, 0, -1);
  }
  return rv;
}

#endif  // ETHANKIM8683_GRAPHS
