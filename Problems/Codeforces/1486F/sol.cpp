#include <bits/stdc++.h>

#include "ethankim8683/trees.hpp"

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

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

  int M;
  cin >> M;

  vector<pair<int, int>> paths(M);
  for (auto &[u, v] : paths) {
    cin >> u >> v;
    u--, v--;
  }

  tree_utils tu(adj);

  vector<int> delta1(N, 0), delta2(N, 0);
  vector<vector<pair<int, int>>> pairs(N);
  int t = -1;
  for (auto [u, v] : paths) {
    int w = tu.lca(u, v);
    if (w != u) {
      delta1[u]++;
      delta2[tu.kth_on_path(w, u, 1)]--;
    }
    if (w != v) {
      delta1[v]++;
      delta2[tu.kth_on_path(w, v, 1)]--;
    }

    int u2 = w == u ? t-- : tu.kth_on_path(w, u, 1),
        v2 = w == v ? t-- : tu.kth_on_path(w, v, 1);
    if (u2 > v2) {
      swap(u2, v2);
    }
    pairs[w].push_back({u2, v2});
  }

  i64 ans = 0;
  auto dfs = [&](auto self, int a, int p) -> int {
    int counts0 = 0;
    map<int, int> counts1;
    map<pair<int, int>, int> counts2;
    for (auto [u, v] : pairs[a]) {
      ans += counts0 - counts1[u] - counts1[v] + counts2[make_pair(u, v)];
      counts0++;
      counts1[u]++;
      counts1[v]++;
      counts2[make_pair(u, v)]++;
    }

    int rv = delta1[a];
    ans += (i64) delta1[a] * counts0;
    for (auto b : adj[a]) {
      if (b == p) continue;
      auto sum = self(self, b, a);
      ans += (i64) sum * (counts0 - counts1[b]);
      rv += sum;
    }
    rv += delta2[a];
    return rv;
  };
  dfs(dfs, 0, -1);
  cout << ans;
}
