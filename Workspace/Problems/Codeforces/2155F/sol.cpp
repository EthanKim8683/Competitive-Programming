#include <bits/stdc++.h>

using namespace std;

const int MAXS = 3e5;
const int SQRTS = sqrt(MAXS);

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K, S, Q;
    cin >> N >> K >> S >> Q;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<vector<int>> C(N);
    for (int i = 0; i < S; i++) {
      int v, x;
      cin >> v >> x;
      v--, x--;
      C[v].push_back(x);
    }

    vector<pair<int, int>> queries(Q);
    for (auto &[u, v] : queries) {
      cin >> u >> v;
      u--, v--;
    }

    vector<vector<int>> by_C(K);
    for (int i = 0; i < N; i++) {
      for (auto e : C[i]) {
        by_C[e].push_back(i);
      }
    }

    vector<int> parent(N), depth(N), tin(N);
    int t = 0;
    auto dfs = [&](auto self, int a, int p, int d) -> void {
      parent[a] = p;
      depth[a] = d;
      tin[a] = t;
      t++;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
    };
    dfs(dfs, 0, -1, 0);

    vector<vector<int>> trees(N);
    vector<int> is_root(N, -1);
    int m = 0;
    for (int i = 0; i < K; i++) {
      sort(by_C[i].begin(), by_C[i].end(),
           [&](int a, int b) -> bool { return tin[a] < tin[b]; });

      vector<pair<int, int>> stack;
      for (auto e : by_C[i]) {
        bool found = false;
        while (stack.size() > 0) {
          auto &[p, j] = stack.back();
          bool pop = false;
          while (depth[p] >= depth[e]) {
            if (is_root[p] == i) {
              pop = true;
              break;
            }
            p = parent[p];
          }
          if (pop) {
            stack.pop_back();
            continue;
          }

          if (p == parent[e]) {
            found = true;
            p = e;
            trees[e].push_back(j);
          }
          break;
        }

        if (!found) {
          int j = m;
          m++;
          is_root[e] = i;
          stack.emplace_back(e, j);
          trees[e].push_back(j);
        }
      }
    }

    for (auto &[u, v] : queries) {
      if (trees[v].size() > trees[u].size()) {
        swap(u, v);
      }
    }

    vector<vector<int>> by_u(N);
    for (int i = 0; i < Q; i++) {
      auto [u, v] = queries[i];
      by_u[u].push_back(i);
    }

    vector<vector<int>> by_tree(m);
    for (int i = 0; i < N; i++) {
      for (auto e : trees[i]) {
        by_tree[e].push_back(i);
      }
    }

    vector<int> ans(Q);
    for (int i = 0; i < N; i++) {
      if (trees[i].size() < SQRTS) {
        for (auto e : by_u[i]) {
          auto [u, v] = queries[e];
          ans[e] = 0;
          int j = 0;
          for (auto e2 : trees[v]) {
            for (; j < trees[u].size(); j++) {
              if (trees[u][j] > e2) break;
              if (trees[u][j] == e2) {
                ans[e]++;
              }
            }
          }
        }
      } else {
        vector<int> counts(N, 0);
        for (auto e : trees[i]) {
          for (auto e2 : by_tree[e]) {
            counts[e2]++;
          }
        }

        for (auto e : by_u[i]) {
          auto [u, v] = queries[e];
          ans[e] = counts[v];
        }
      }
    }
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
