#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1ll << 60;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<vector<pair<int, i64>>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    i64 w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  vector<bool> seen(N, false);
  i64 ans = INF;
  auto dfs = [&](auto self, int a, i64 s) -> void {
    if (seen[a]) return;
    seen[a] = true;
    if (a == N - 1) {
      ans = min(ans, s);
    } else {
      for (auto [b, w] : adj[a]) {
        self(self, b, s ^ w);
      }
    }
    seen[a] = false;
  };
  dfs(dfs, 0, 0);
  cout << ans;
}
