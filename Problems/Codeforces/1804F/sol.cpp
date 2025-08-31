#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, Q;
  cin >> N >> M >> Q;

  vector<vector<pair<int, int>>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back({v, 0});
    adj[v].push_back({u, 0});
  }

  for (int i = 1; i <= Q; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back({v, i});
    adj[v].push_back({u, i});
  }

  // If all nodes are distance at most x from a node, x is at least ceil(d/2)
  //
  // If there exists a node distance at least y from a node, y is strictly less
  // than d
  //
  // If y = x/2, then x is at least ceil(d/2) and (x = 2y) < 2d.
  //
  // Thus, we only need to keep track of the distances from one node. Since we
  // only need to find a pair (x, x/2) where all nodes are within distance x but
  // not distance x/2, we can try x = 2^k for various k.

  vector<int> dist(N, INF);
  queue<int> q;
  map<int, int> memo;
  auto max_dist = [&](int k) -> int {
    if (memo.contains(k)) return memo[k];
    fill(dist.begin(), dist.end(), INF);
    auto push = [&](int d, int a) -> void {
      if (d >= dist[a]) return;
      dist[a] = d;
      q.push(a);
    };
    push(0, 0);
    while (q.size() > 0) {
      int a = q.front();
      q.pop();
      for (auto [b, i] : adj[a]) {
        if (i > k) continue;
        push(dist[a] + 1, b);
      }
    }
    return memo[k] = *max_element(dist.begin(), dist.end());
  };
  auto solve = [&](int x) -> int {
    int l = 0, r = Q + 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      max_dist(m) <= x ? r = m : l = m + 1;
    }
    return l;
  };

  vector<int> ans(Q + 1, INF);
  for (int x = 2; x <= 2 * (N - 1); x *= 2) {
    int i = solve(x);
    if (i <= Q) {
      ans[i] = min(ans[i], x);
    }
  }
  for (int i = 0; i + 1 <= Q; i++) {
    ans[i + 1] = min(ans[i + 1], ans[i]);
  }
  for (auto e : ans) {
    cout << e << ' ';
  }
}
