#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<tuple<int, int, int>> edges(M);
  vector<vector<pair<int, int>>> adj(N);
  for (auto &[a, b, w] : edges) {
    cin >> a >> b >> w;
    a--, b--;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }

  vector<dsu> d(30);
  for (int i = 0; i < 30; i++) {
    d[i] = dsu(N);
    for (auto [a, b, w] : edges) {
      if (w >> i & 1) {
        d[i].merge(a, b);
      }
    }
  }

  vector<bool> ok(N, false);
  for (int i = 1; i < 30; i++) {
    vector<bool> pushed(N, false);
    queue<int> q;
    auto push = [&](int a) -> void {
      if (pushed[a]) return;
      pushed[a] = true;
      ok[a] = true;
      q.push(a);
    };
    for (auto [a, b, w] : edges) {
      if ((w & 1) == 0) {
        push(a);
        push(b);
      }
    }
    while (q.size() > 0) {
      int a = q.front();
      q.pop();
      for (auto [b, w] : adj[a]) {
        if (w >> i & 1) {
          push(b);
        }
      }
    }
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    int ans = 2;
    for (int i = 0; i < 30; i++) {
      if (d[i].same(u, v)) {
        ans = min(ans, 0);
      }
    }
    if (ok[u]) {
      ans = min(ans, 1);
    }
    cout << ans << '\n';
  }
}
