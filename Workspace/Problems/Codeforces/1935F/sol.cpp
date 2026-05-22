#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"
#include "ethankim8683/trees.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

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

    tree_utils tu(adj);
    vector<vector<int>> segs(2 * N);
    for (int i = 0; i < N; i++) {
      segs[tu.get_index(i) + N].push_back(i);
    }
    for (int i = N - 1; i > 0; i--) {
      merge(segs[i << 1].begin(), segs[i << 1].end(), segs[i << 1 | 1].begin(),
            segs[i << 1 | 1].end(), back_inserter(segs[i]));
    }
    auto query = [&](int l1, int r1, int l2, int r2) -> int {
      int rv = -1;
      auto use = [&](int i) -> void {
        auto it = lower_bound(segs[i].begin(), segs[i].end(), r2);
        if (it == segs[i].begin()) return;
        rv = max(rv, *prev(it));
      };
      for (l1 += N, r1 += N; l1 < r1; l1 >>= 1, r1 >>= 1) {
        if (l1 & 1) use(l1++);
        if (r1 & 1) use(--r1);
      }
      return rv < l2 ? -1 : rv;
    };

    vector<int> index(N);
    vector<vector<pair<int, int>>> ans(N);
    auto dfs = [&](auto self, int a, int p = -1) -> void {
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }

      dsu ds(adj[a].size());
      for (int i = 0; i < adj[a].size(); i++) {
        index[adj[a][i]] = i;
      }

      for (auto b : adj[a]) {
        int c1 = -1, c2 = -1;
        if (b == p) {
          auto [l, r] = tu.get_range(a);
          c1 = max(query(0, l, 0, a), query(r, N, 0, a));
          c2 = max(query(0, l, a + 1, N), query(r, N, a + 1, N));
        } else {
          auto [l, r] = tu.get_range(b);
          c1 = query(l, r, 0, a);
          c2 = query(l, r, a + 1, N);
        }

        if (c1 != -1) {
          int c = c1, d = c + 1;
          if (d < a) {
            int c_ = index[tu.kth_on_path(a, c, 1)],
                d_ = index[tu.kth_on_path(a, d, 1)];
            if (!ds.same(c_, d_)) {
              ds.merge(c_, d_);
              ans[a].push_back({c, d});
            }
          }
        }

        if (c2 != -1) {
          int c = c2, d = c + 1;
          if (d < N) {
            int c_ = index[tu.kth_on_path(a, c, 1)],
                d_ = index[tu.kth_on_path(a, d, 1)];
            if (!ds.same(c_, d_)) {
              ds.merge(c_, d_);
              ans[a].push_back({c, d});
            }
          }
        }
      }

      if (ans[a].size() < adj[a].size() - 1) {
        ans[a].push_back({a - 1, a + 1});
      }
    };
    dfs(dfs, 0, -1);

    for (int i = 0; i < N; i++) {
      int w = 0;
      for (auto [a, b] : ans[i]) {
        w += abs(a - b);
      }

      cout << w << ' ' << ans[i].size() << '\n';
      for (auto [a, b] : ans[i]) {
        cout << a + 1 << ' ' << b + 1 << '\n';
      }
      cout << '\n';
    }
  }
}
