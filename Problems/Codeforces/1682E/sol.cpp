#include <bits/stdc++.h>

#include "ethankim8683/graphs.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> P(N);
  for (auto &e : P) cin >> e, e--;

  vector<pair<int, int>> swaps(M);
  for (auto &[x, y] : swaps) {
    cin >> x >> y;
    x--, y--;
  }

  vector<vector<pair<int, int>>> adj(N);
  for (int i = 0; i < M; i++) {
    auto [x, y] = swaps[i];
    adj[x].push_back({y, i});
    adj[y].push_back({x, i});
  }

  vector<bool> seen(N, false);
  vector<int> depth(N), length(N);
  auto dfs = [&](auto self, int a, int d) -> int {
    if (seen[a]) return d;
    seen[a] = true;
    depth[a] = d;
    return length[a] = self(self, P[a], d + 1);
  };
  for (int i = 0; i < N; i++) {
    dfs(dfs, i, 0);
  }

  vector<vector<int>> adj2(M);
  for (int a = 0; a < N; a++) {
    sort(adj[a].begin(), adj[a].end(),
         [&](pair<int, int> e1, pair<int, int> e2) {
           auto key = [&](pair<int, int> e) -> int {
             int b = e.first;
             return (depth[b] - depth[a] + length[a]) % length[a];
           };
           return key(e1) < key(e2);
         });
    for (int i = 0; i + 1 < adj[a].size(); i++) {
      adj2[adj[a][i].second].push_back(adj[a][i + 1].second);
    }
  }
  for (auto e : toposort(adj2)) {
    cout << e + 1 << ' ';
  }
}
