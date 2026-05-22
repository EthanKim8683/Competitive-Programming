#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<int> ans(N);
    int t = 1;
    auto dfs = [&](auto self, int a, int p) -> void {
      ans[a] = t;
      t++;
      bool flag = false;
      for (auto b : adj[a]) {
        if (b == p) continue;
        if (flag) {
          while (t % 2 != ans[a] % 2 or t - ans[a] == 2) {
            t++;
          }
        } else {
          flag = true;
        }
        self(self, b, a);
      }
    };
    dfs(dfs, 0, -1);

    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
