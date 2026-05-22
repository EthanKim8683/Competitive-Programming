#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<vector<pair<int, int>>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v, y;
    cin >> u >> v >> y;
    u--, v--;
    adj[u].push_back({v, y});
    adj[v].push_back({u, y});
  }

  vector<i64> dist(N, INF);
  priority_queue<pair<i64, int>> pq;
  auto push = [&](i64 d, int a) -> void {
    if (d >= dist[a]) return;
    dist[a] = d;
    pq.push({-d, a});
  };
  push(0, N - 1);
  while (pq.size() > 0) {
    auto [d, a] = pq.top();
    pq.pop();
    if ((d = -d) != dist[a]) continue;
    for (auto [b, y] : adj[a]) {
      push(d + y, b);
    }
  }

  if (dist[0] == INF) {
    cout << "inf";
    exit(0);
  }

  for (auto &e : dist) {
    e = min(e, dist[0]);
  }
  map<i64, int> index;
  for (auto e : dist) {
    index[e] = 0;
  }
  vector<i64> depth(index.size());
  int t = 0;
  for (auto &[k, v] : index) {
    v = t++;
    depth[v] = k;
  }

  cout << dist[0] << ' ' << index.size() - 1 << '\n';
  for (int i = 0; i < index.size() - 1; i++) {
    for (int j = 0; j < N; j++) {
      cout << (i < index[dist[j]]);
    }
    cout << ' ' << depth[i + 1] - depth[i] << '\n';
  }
}
