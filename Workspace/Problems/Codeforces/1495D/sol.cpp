#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> adj(N);
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // non-path nodes must orient towards shallower nodes in both trees

  vector dist(N, vector<int>(N, INF));
  queue<int> q;
  for (int r = 0; r < N; r++) {
    auto push = [&](int d, int a) -> void {
      if (d >= dist[r][a]) return;
      dist[r][a] = d;
      q.push(a);
    };
    push(0, r);
    while (q.size() > 0) {
      int a = q.front();
      q.pop();
      for (auto b : adj[a]) {
        push(dist[r][a] + 1, b);
      }
    }
  }

  vector ans(N, vector<mint>(N, 0));
  for (int s = 0; s < N; s++) {
    for (int t = 0; t < N; t++) {
      int count = 0;
      for (int a = 0; a < N; a++) {
        if (dist[s][a] + dist[a][t] == dist[s][t]) {
          count++;
        }
      }
      if (count > dist[s][t] + 1) continue;

      ans[s][t] = 1;
      for (int a = 0; a < N; a++) {
        if (dist[s][a] + dist[a][t] == dist[s][t]) continue;

        mint count = 0;
        for (auto b : adj[a]) {
          if (dist[s][b] < dist[s][a] and dist[t][b] < dist[t][a]) {
            count++;
          }
        }
        ans[s][t] *= count;
      }
    }
  }
  for (auto r : ans) {
    for (auto e : r) {
      cout << e.val() << ' ';
    }
    cout << '\n';
  }
}
