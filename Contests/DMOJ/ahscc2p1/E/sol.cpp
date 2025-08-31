#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 2e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, K;
  i64 T;
  cin >> N >> M >> K >> T;

  vector<int> P(K);
  for (auto &e : P) cin >> e, e--;

  vector<vector<pair<int, int>>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    u--, v--;
    adj[u].push_back({v, d});
    adj[v].push_back({u, d});
  }

  vector<i64> dist(N, INF);
  priority_queue<pair<i64, int>> pq;
  auto push = [&](i64 d, int a) -> void {
    if (d >= dist[a]) return;
    dist[a] = d;
    pq.push({-d, a});
  };
  vector<bool> no(N, true);
  for (auto e : P) {
    no[e] = false;
  }
  for (int i = 0; i < N; i++) {
    if (no[i]) {
      push(0, i);
    }
  }
  while (pq.size() > 0) {
    auto [d, a] = pq.top();
    pq.pop();
    if ((d = -d) != dist[a]) continue;
    for (auto [b, w] : adj[a]) {
      push(d + w, b);
    }
  }
  string ans(N, '0');
  for (auto e : P) {
    ans[e] = '0' + (dist[e] > T);
  }
  cout << ans;
}
