#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  // 2<=M<=N+1

  if (!(2 <= M and M <= N + 1)) {
    cout << -1;
    exit(0);
  }

  vector<vector<int>> adj(N);
  for (int i = 0; i + 1 < N; i++) {
    adj[i].push_back(i + 1);
  }
  for (int i = 0; i <= N; i++) {
    adj[min(N - i, N - 1)].push_back(N + min(i, M - 1));
  }

  for (auto r : adj) {
    for (auto e : r) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
