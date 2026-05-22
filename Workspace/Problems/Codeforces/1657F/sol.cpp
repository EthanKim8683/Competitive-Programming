#include <bits/stdc++.h>

#include "atcoder/twosat.hpp"
#include "ethankim8683/trees.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<vector<int>> adj(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<tuple<int, int, string>> queries(Q);
  for (auto &[x, y, s] : queries) {
    cin >> x >> y >> s;
    x--, y--;
  }

  tree_utils tu(adj);
  vector<array<char, 2>> opts(N, {'a', 'b'});
  for (auto [x, y, s] : queries) {
    for (int i = 0; i < s.size(); i++) {
      opts[tu.kth_on_path(x, y, i)] = {s[i], s[s.size() - 1 - i]};
    }
  }

  two_sat ts(Q + N * 2);
  for (int i = 0; i < Q; i++) {
    auto [x, y, s] = queries[i];
    for (int j = 0; j < s.size(); j++) {
      int a = tu.kth_on_path(x, y, j);
      char c1 = s[j], c2 = s[s.size() - 1 - j];
      for (int k = 0; k < 2; k++) {
        if (opts[a][k] != c1) {
          ts.add_clause(Q + a * 2 + k, false, i, true);
        }
        if (opts[a][k] != c2) {
          ts.add_clause(Q + a * 2 + k, false, i, false);
        }
      }
    }
  }
  for (int i = 0; i < N; i++) {
    ts.add_clause(Q + i * 2, true, Q + i * 2 + 1, true);
    ts.add_clause(Q + i * 2, false, Q + i * 2 + 1, false);
  }

  if (!ts.satisfiable()) {
    cout << "NO\n";
    exit(0);
  }

  auto sol = ts.answer();
  vector<char> ans(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 2; j++) {
      if (sol[Q + i * 2 + j]) {
        ans[i] = opts[i][j];
      }
    }
  }

  cout << "YES\n";
  for (auto e : ans) {
    cout << e;
  }
}
