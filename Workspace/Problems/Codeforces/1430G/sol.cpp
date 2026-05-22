#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<vector<pair<int, int>>> adj(N), radj(N);
  for (int i = 0; i < M; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    x--, y--;
    adj[y].push_back({x, w});
    radj[x].push_back({y, w});
  }

  vector<bool> seen(N, false);
  vector<int> order;
  auto dfs = [&](auto self, int a) -> void {
    if (seen[a]) return;
    seen[a] = true;
    for (auto [b, w] : adj[a]) {
      self(self, b);
    }
    order.push_back(a);
  };
  for (int i = 0; i < N; i++) {
    dfs(dfs, i);
  }
  reverse(order.begin(), order.end());

  vector<int> dist(N, 0);
  for (auto a : order) {
    for (auto [b, w] : adj[a]) {
      dist[b] = max(dist[b], dist[a] + 1);
    }
  }
}
