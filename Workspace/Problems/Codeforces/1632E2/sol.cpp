#include <bits/stdc++.h>

#include "ethankim8683/trees.hpp"

using namespace std;

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
    int max_depth = 0;
    for (int i = 0; i < N; i++) {
      max_depth = max(max_depth, tu.get_depth(i));
    }
    vector<vector<int>> by_depth(max_depth + 1);
    for (int i = 0; i < N; i++) {
      by_depth[tu.get_depth(i)].push_back(i);
    }

    vector<int> diameter(max_depth);
    int f1 = -1, f2;
    for (int i = max_depth - 1; i >= 0; i--) {
      for (auto a : by_depth[i + 1]) {
        if (f1 == -1) {
          f1 = f2 = a;
        } else {
          if (tu.dist(f1, a) > tu.dist(f1, f2)) {
            f2 = a;
          }
          if (tu.dist(f2, a) > tu.dist(f1, f2)) {
            f1 = a;
          }
        }
      }
      diameter[i] = tu.dist(f1, f2);
    }

    for (int i = 1; i <= N; i++) {
      auto check = [&](int d) -> int { return i + (diameter[d] + 1) / 2 <= d; };

      int l = 0, r = max_depth;
      while (l < r) {
        int m = l + (r - l) / 2;
        check(m) ? r = m : l = m + 1;
      }
      cout << l << ' ';
    }
    cout << '\n';
  }
}
