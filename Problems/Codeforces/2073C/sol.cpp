#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<bool> seen(N, false);
  vector<int> depth(N), tin(N), tmin(N);
  int ans = 1, t = 0;
  auto dfs = [&](auto self, int a, int p, int d) -> void {
    seen[a] = true;
    depth[a] = d;

    tmin[a] = tin[a] = t;
    t++;

    for (auto b : adj[a]) {
      if (b == p) continue;

      if (seen[b]) {
        if (depth[b] < d) {
          ans += (d + 1 - depth[b]) / 2 * 2;
        }

        tmin[a] = min(tmin[a], tin[b]);
      } else {
        self(self, b, a, d + 1);

        tmin[a] = min(tmin[a], tmin[b]);
        if (tmin[b] > tin[a]) {
          ans += 1;
        }
      }
    }
  };
  for (int i = 0; i < N; i++) {
    if (seen[i]) continue;
    dfs(dfs, i, -1, 0);
  }
  cout << ans << '\n';
}
