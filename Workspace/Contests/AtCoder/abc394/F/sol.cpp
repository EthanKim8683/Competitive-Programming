#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<vector<int>> adj(N);
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<bool> seen(N, false);
  int ans = 0;
  auto dfs = [&](auto self, int a, int p) -> int {
    if (adj[a].size() < 4) return 0;
    if (seen[a]) return 0;
    seen[a] = true;

    vector<int> sub;
    for (auto b : adj[a]) {
      if (b == p) continue;
      sub.push_back(self(self, b, a));
    }
    sort(sub.rbegin(), sub.rend());
    if (sub.size() >= 4) {
      int sum = 1;
      for (int i = 0; i < 4; i++) {
        sum += sub[i];
      }
      ans = max(ans, sum);
    }
    int sum = 1;
    for (int i = 0; i < 3; i++) {
      sum += sub[i];
    }
    return sum;
  };
  for (int i = 0; i < N; i++) {
    dfs(dfs, i, -1);
  }
  if (ans == 0) {
    cout << -1;
  } else {
    cout << ans * 4 - (ans - 1) + 1;
  }
}
