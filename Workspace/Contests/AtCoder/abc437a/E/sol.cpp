#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<int, int>> appends(N);
  for (auto &[x, y] : appends) {
    cin >> x >> y;
  }

  vector<map<int, int>> adj;
  adj.emplace_back();
  vector<int> node(N + 1);
  node[0] = 0;
  for (int i = 0; i < N; i++) {
    auto [x, y] = appends[i];
    int a = node[x];
    if (!adj[a].contains(y)) {
      adj[a][y] = adj.size();
      adj.emplace_back();
    }
    node[i + 1] = adj[a][y];
  }

  vector<vector<int>> sequences(adj.size());
  for (int i = 1; i <= N; i++) {
    sequences[node[i]].push_back(i);
  }

  vector<int> ans;
  auto dfs = [&](auto self, int a) -> void {
    for (auto e : sequences[a]) {
      ans.push_back(e);
    }
    for (auto [y, b] : adj[a]) {
      self(self, b);
    }
  };
  dfs(dfs, 0);
  for (auto e : ans) {
    cout << e << ' ';
  }
}
