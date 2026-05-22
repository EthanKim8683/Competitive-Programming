#ifndef ETHANKIM8683_GRAPH
#define ETHANKIM8683_GRAPH 1

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <queue>
#include <vector>

namespace ethankim8683 {

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

  std::vector<int> degree(n, 0);
  for (auto adja : adj) {
    for (auto b : adja) {
      degree[b]++;
    }
  }

  auto rcmp = [&](int a, int b) -> bool { return cmp(b, a); };
  std::priority_queue<int, std::vector<int>, decltype(rcmp)> pq(rcmp);
  auto nudge = [&](int a) -> void {
    if (degree[a] != 0) return;
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
      if (degree[b] == 0) continue;
      degree[b]--;
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

// https://judge.yosupo.jp/submission/339108
struct mbm_graph {
 private:
  int n, m;
  std::vector<std::vector<int>> adj;
  std::vector<int> mate;

 public:
  mbm_graph(int _n, int _m) : n(_n), m(_m), adj(n + m), mate(n + m, -1) {}

  void add_edge(int l, int r) {
    adj[l].push_back(n + r);
    adj[n + r].push_back(l);
  }

  int match() {
    std::queue<int> q1;
    for (int i = n; i < n + m; i++) {
      q1.push(i);
    }
    while (true) {
      std::vector<int> depth(n + m, std::numeric_limits<int>::max());
      std::queue<int> q2;
      for (int i = 0; i < n; i++) {
        if (mate[i] != -1) continue;
        depth[i] = 0;
        q2.push(i);
      }
      while (q2.size() > 0) {
        int a = q2.front();
        q2.pop();

        for (auto b : adj[a]) {
          if (depth[a] + 1 >= depth[b]) continue;
          depth[b] = depth[a] + 1;

          int c = mate[b];
          if (c != -1) {
            depth[c] = depth[b] + 1;
            q2.push(c);
          }
        }
      }

      for (int i = 0; i < n + m; i++) {
        if (q1.empty()) {
          return (n + m - count(mate.begin(), mate.end(), -1)) / 2;
        }

        int a = q1.front();
        q1.pop();

        int d = std::numeric_limits<int>::max(), b;
        for (auto c : adj[a]) {
          if (depth[c] >= d) continue;
          d = depth[c];
          b = c;
        }
        if (d < std::numeric_limits<int>::max()) {
          depth[a] = depth[b] + 1;

          int c = mate[b];
          if (c != -1) {
            mate[c] = -1;
            q1.push(c);
          }

          mate[a] = b;
          mate[b] = a;
          depth[b] += 2;
        }
      }
    }
  }

  std::vector<std::pair<int, int>> matching() {
    std::vector<std::pair<int, int>> rv;
    for (int i = 0; i < n; i++) {
      if (mate[i] == -1) continue;
      rv.push_back({i, mate[i] - n});
    }
    return rv;
  }

  std::vector<std::vector<int>> minimum_chain_cover() {
    assert(n == m);
    std::vector<std::vector<int>> rv;
    for (int i = 0; i < n; i++) {
      if (mate[n + i] != -1) continue;

      std::vector<int> chain;
      int a = i;
      while (a >= 0) {
        chain.push_back(a);
        a = mate[a] - n;
      }
      rv.push_back(chain);
    }
    return rv;
  }
};

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

}  // namespace ethankim8683

#endif  // ETHANKIM8683_GRAPH
