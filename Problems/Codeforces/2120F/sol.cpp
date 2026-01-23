#include <bits/stdc++.h>

#include "atcoder/twosat.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<vector<int>> indeps, cliques;
    for (int i = 0; i < K; i++) {
      int M;
      cin >> M;

      vector adj(N, vector<int>(N, 0));
      for (int j = 0; j < M; j++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u][v] = adj[v][u] = 1;
      }

      vector adj2 = adj;
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          if (j == k) continue;
          adj2[j][k] ^= 1;
        }
      }

      map<vector<int>, vector<int>> sets, sets2;
      for (int i = 0; i < N; i++) {
        sets[adj[i]].push_back(i);
        sets2[adj2[i]].push_back(i);
      }
      for (auto [k, v] : sets) {
        indeps.push_back(v);
      }
      for (auto [k, v] : sets2) {
        cliques.push_back(v);
      }
    }

    two_sat ts(N);
    for (auto r : indeps) {
      for (int i = 0; i < r.size(); i++) {
        for (int j = i + 1; j < r.size(); j++) {
          ts.add_clause(r[i], false, r[j], false);
        }
      }
    }
    for (auto r : cliques) {
      for (int i = 0; i < r.size(); i++) {
        for (int j = i + 1; j < r.size(); j++) {
          ts.add_clause(r[i], true, r[j], true);
        }
      }
    }
    cout << (ts.satisfiable() ? "Yes" : "No") << '\n';
  }
}
