#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<vector<pair<int, int>>> adj(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v, p;
    cin >> u >> v >> p;
    adj[u].push_back({v, p});
    adj[v].push_back({u, p});
  }

  i64 ans = 0;
  for (int i = 0; i < N; i++) {
    i64 P = 0, p_ = 0;
    for (auto [b, p] : adj[i]) {
      P += p;
      p_ = max(p_, (i64) p);
    }

    if (2 * p_ > P) {
      ans += p_ - (P - p_);
    } else if (P % 2 == 1) {
      ans += 1;
    }
  }
  cout << ans / 2;
}