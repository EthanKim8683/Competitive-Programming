#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"
#include "ethankim8683/trees.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int Q;
    cin >> Q;

    vector<array<int, 3>> queries(Q);
    for (auto &[t, v, x] : queries) {
      cin >> t >> v;
      v--;
      if (t == 2) {
        cin >> x;
      }
    }

    vector<vector<int>> adj = {{}};
    int N = 1;
    for (auto [t, v, x] : queries) {
      if (t == 1) {
        adj[v].push_back(N++);
        adj.push_back({});
      }
    }
    tree_utils tu(adj);
    fenwick_tree<i64> ft(N + 1);
    int i = 1;
    for (auto [t, v, x] : queries) {
      if (t == 1) {
        auto [l, r] = tu.get_range(i++);
        i64 x = ft.sum(0, l + 1);
        ft.add(l, -x);
        ft.add(r, x);
      }
      if (t == 2) {
        auto [l, r] = tu.get_range(v);
        ft.add(l, x);
        ft.add(r, -x);
      }
    }
    for (int i = 0; i < N; i++) {
      cout << ft.sum(0, tu.get_index(i) + 1) << ' ';
    }
    cout << '\n';
  }
}
