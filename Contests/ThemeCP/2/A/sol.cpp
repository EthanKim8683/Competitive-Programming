#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"
#include "ethankim8683/tree.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<tuple<int, int, int>> edges(M);
    for (auto &[w, u, v] : edges) {
      cin >> u >> v >> w;
      u--, v--;
    }
    sort(edges.rbegin(), edges.rend());

    dsu d(N);
    vector<vector<int>> adj(N);
    int b, uc, vc;
    for (auto [w, u, v] : edges) {
      if (d.same(u, v)) {
        b = w;
        uc = u;
        vc = v;
      } else {
        adj[u].push_back(v);
        adj[v].push_back(u);
        d.merge(u, v);
      }
    }

    euler_tour et(adj, uc);
    int k = et.dist(uc, vc) + 1;
    cout << b << ' ' << k << '\n';
    for (int i = 0; i < k; i++) {
      cout << et.kth_on_path(uc, vc, i) + 1 << ' ';
    }
    cout << '\n';
  }
}
