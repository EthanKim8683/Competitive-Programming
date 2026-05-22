#include <bits/stdc++.h>

#include "ethankim8683/graphs.hpp"

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<int> deg(N);
    for (int i = 0; i < N; i++) {
      deg[i] = adj[i].size();
    }

    vector<vector<int>> adj_(N);
    queue<int> q;
    auto nudge = [&](int a) -> void {
      if (deg[a] != A[a]) return;
      q.push(a);
    };
    for (int i = 0; i < N; i++) {
      nudge(i);
    }
    while (q.size() > 0) {
      int a = q.front();
      q.pop();
      for (auto b : adj[a]) {
        if (deg[b] == A[b]) continue;
        deg[b]--;
        adj_[a].push_back(b);
        nudge(b);
      }
    }
  }
}
