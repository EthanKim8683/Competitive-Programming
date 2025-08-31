#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    auto cull = [&](int k) -> vector<bool> {
      vector<set<int>> adj2(N);
      for (int a = 0; a < N; a++) {
        for (auto b : adj[a]) {
          adj2[a].insert(b);
        }
      }

      vector<bool> rv(N, true);
      queue<int> q;
      auto nudge = [&](int a) -> void {
        if (adj2[a].size() >= k or !rv[a]) return;
        rv[a] = false;
        q.push(a);
      };
      for (int a = 0; a < N; a++) {
        nudge(a);
      }
      while (q.size() > 0) {
        int a = q.front();
        q.pop();
        for (auto b : adj2[a]) {
          adj2[b].erase(a);
          nudge(b);
        }
        adj2[a].clear();
      }
      return rv;
    };

    auto g = cull(K);
    if (find(g.begin(), g.end(), true) != g.end()) {
      vector<int> ans;
      for (int a = 0; a < N; a++) {
        if (!g[a]) continue;
        ans.push_back(a);
      }
      cout << 1 << ' ' << ans.size() << '\n';
      for (auto e : ans) {
        cout << e + 1 << ' ';
      }
      cout << '\n';
      continue;
    }

    if ((i64) K * (K - 1) / 2 > M) {
      cout << -1 << '\n';
      continue;
    }

    for (int a = 0; a < N; a++) {
      sort(adj[a].begin(), adj[a].end());
    }
    auto check = [&](vector<int> C) -> bool {
      sort(C.begin(), C.end());
      for (auto a : C) {
        int i = 0;
        for (auto b : adj[a]) {
          while (i < C.size() and (a == C[i] or b == C[i])) {
            i++;
          }
        }
        if (i != C.size()) return false;
      }
      return true;
    };

    g = cull(K - 1);
    vector<vector<int>> adj2(N);
    for (int a = 0; a < N; a++) {
      if (!g[a]) continue;
      for (auto b : adj[a]) {
        if (!g[b]) continue;
        adj2[a].push_back(b);
      }
    }

    vector<bool> seen(N, false);
    vector<int> ans;
    for (int a = 0; a < N; a++) {
      if (adj2[a].size() != K - 1 or seen[a]) continue;

      auto C = adj2[a];
      C.push_back(a);
      if (check(C)) {
        ans = C;
        break;
      }

      for (auto e : C) {
        seen[e] = true;
      }
    }

    if (ans.empty()) {
      cout << -1 << '\n';
      continue;
    }

    cout << 2 << '\n';
    for (auto e : ans) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
