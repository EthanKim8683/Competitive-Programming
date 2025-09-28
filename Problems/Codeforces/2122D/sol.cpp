#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
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

    // we could go for M seconds and fill up all node/edge pair states

    vector<vector<pair<int, int>>> dist(N);
    for (int i = 0; i < N; i++) {
      dist[i].resize(adj[i].size(), {INF, INF});
    }
    queue<pair<int, int>> q;
    auto push = [&](int a, int d, int w) -> void {
      int i = d % adj[a].size();
      pair<int, int> dw = {d, w};
      if (dw >= dist[a][i]) return;
      dist[a][i] = dw;
      q.push({a, i});
    };
    push(0, 0, 0);
    while (q.size() > 0) {
      auto [a, i] = q.front();
      q.pop();
      auto [d, w] = dist[a][i];
      int k = adj[a].size();
      for (int j = 0; j < k; j++) {
        int c = (j - d % k + k) % k;
        push(adj[a][j], d + c + 1, w + c);
      }
    }
    auto [d, w] = *min_element(dist[N - 1].begin(), dist[N - 1].end());
    cout << d << ' ' << w << '\n';
  }
}