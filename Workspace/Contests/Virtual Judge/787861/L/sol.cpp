#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // add edge if distances are consistent
  //
  // vector of parents

  int N, M, D;
  cin >> N >> M >> D;

  vector<vector<pair<int, int>>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v, h;
    cin >> u >> v >> h;
    u--, v--;
    adj[u].emplace_back(v, h);
  }

  vector<i64> T(D);
  for (auto &e : T) cin >> e;
  sort(T.begin(), T.end());

  vector<i64> dist(N, INF);
  priority_queue<pair<i64, int>> pq;
  auto push = [&](int a, i64 d) -> void {
    if (d >= dist[a]) return;
    dist[a] = d;
    pq.emplace(-d, a);
  };
  push(0, 0);
  while (pq.size() > 0) {
    auto [d, a] = pq.top();
    pq.pop();
    if ((d = -d) != dist[a]) continue;
    for (auto [b, w] : adj[a]) {
      push(b, d + w);
    }
  }
  if (T.back() > dist[N - 1]) {
    cout << "0\n";
    exit(0);
  }

  vector<bool> seen(N, false);
  vector<vector<int>> parents(N);
  auto dfs = [&](auto self, int a) -> void {
    if (seen[a]) return;
    seen[a] = true;

    auto it = upper_bound(T.begin(), T.end(), dist[a]);
    for (auto [b, w] : adj[a]) {
      if (dist[b] != dist[a] + w) continue;
      if (it != T.end() and dist[b] > *it) continue;
      parents[b].push_back(a);
      self(self, b);
    }
  };
  dfs(dfs, 0);
  if (!seen[N - 1]) {
    cout << "0\n";
    exit(0);
  }

  vector<int> ans;
  auto dfs2 = [&](auto self, int a) -> void {
    if (parents[a].size() > 1) {
      cout << "1\n";
      exit(0);
    }

    ans.push_back(a);
    for (auto b : parents[a]) {
      self(self, b);
    }
  };
  dfs2(dfs2, N - 1);
  reverse(ans.begin(), ans.end());

  cout << ans.size() << '\n';
  for (auto e : ans) {
    cout << e + 1 << '\n';
  }
}
