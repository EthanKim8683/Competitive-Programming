#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int K, N, M;
  cin >> K >> N >> M;

  vector adj(N, vector<vector<pair<int, int>>>(K));
  for (int i = 0; i < M; i++) {
    int u, v, d, z;
    cin >> u >> v >> d >> z;
    u--, v--, d--;
    adj[d][u].push_back({v, z});
  }

  vector count(N + 1, vector<int>(K, 0));
  for (int i = 0; i < K * N; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    count[b][a] += c;
  }

  bool ok = true;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      for (auto [k, c] : adj[i][j]) {
        ok = ok and count[i][j] >= c;
        count[i][j] -= c;
        count[i + 1][k] += c;
      }
      count[i + 1][j] += count[i][j];
    }
  }
  cout << (ok ? "optimal" : "suboptimal");
}