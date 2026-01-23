#include <bits/stdc++.h>

#include "ethankim8683/tree.hpp"

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // start: 12:34
  // thinking done: 12:45
  // target impl time: 20 min
  // initial impl done: 12:58

  // find the centroid, sum of distances to centroid
  // subtract d * n, where d is the depth of the node and n is the size of its
  // subtree
  //
  // is the centroid expected to change? no. each subtree is at most (n-1)/2 in
  // size, satisfying odd
  //
  // find centroid, then find node to merge

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

    int c = find_centroids(adj)[0];

    tuple<i64, int, int> best = {INF, -1, -1};
    auto dfs = [&](auto self, int a, int p, int d) -> int {
      int n = 1;
      for (auto b : adj[a]) {
        if (b == p) continue;
        n += self(self, b, a, d + 1);
      }
      if (a != c) {
        best = min(best, tuple{(i64) d * n, a, p});
      }
      return n;
    };
    dfs(dfs, c, -1, 0);
    auto [cost, u, v] = best;
    if (u > v) {
      swap(u, v);
    }

    auto relabel = [&](int a) -> int {
      if (a == v) return u;
      return a;
    };
    vector<vector<int>> adj2(N);
    for (int i = 0; i < N; i++) {
      for (auto b : adj[i]) {
        if (relabel(i) == relabel(b)) continue;
        adj2[relabel(i)].push_back(relabel(b));
      }
    }
    int c2 = relabel(c);

    vector<vector<int>> parts;
    auto dfs2 = [&](auto self, int a, int p) -> void {
      parts.back().push_back(a);
      for (auto b : adj2[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    };
    for (auto b : adj2[c2]) {
      parts.emplace_back();
      dfs2(dfs2, b, c2);
    }
    parts.push_back({c2});

    priority_queue<pair<int, int>> pq;
    auto nudge = [&](int i) -> void {
      if (parts[i].empty()) return;
      pq.emplace(parts[i].size(), i);
    };
    for (int i = 0; i < parts.size(); i++) {
      nudge(i);
    }
    vector<int> ans(N, 0);
    int t = 1;
    while (pq.size() > 0) {
      auto [n1, i] = pq.top();
      pq.pop();
      auto [n2, j] = pq.top();
      pq.pop();

      int a = parts[i].back(), b = parts[j].back();
      parts[i].pop_back();
      parts[j].pop_back();

      ans[a] = ans[b] = t;
      t++;

      nudge(i);
      nudge(j);
    }

    cout << u + 1 << ' ' << v + 1 << '\n';
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
