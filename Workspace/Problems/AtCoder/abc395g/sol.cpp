#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector C(N, vector<int>(N));
  for (auto &r : C) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vector dist(N, vector<i64>(1 << K, INF));
  priority_queue<tuple<i64, int, int>> pq;
  auto push = [&](i64 d, int a, int mask) -> void {
    if (d >= dist[a][mask]) return;
    dist[a][mask] = d;
    pq.push({-d, a, mask});
  };
  for (int i = 0; i < K; i++) {
    push(0, i, 1 << i);
  }
  while (pq.size() > 0) {
    auto [d, a, mask] = pq.top();
    pq.pop();
    if ((d = -d) != dist[a][mask]) continue;
    for (int i = 0; i < (1 << K); i++) {
      if (mask & i) continue;
      push(d + dist[a][i], a, mask | i);
    }
    for (int b = 0; b < N; b++) {
      push(d + C[a][b], b, mask);
    }
  }

  vector dist2(N, vector(N, vector<i64>(1 << K, INF)));
  for (int r = 0; r < N; r++) {
    auto push = [&](i64 d, int a, int mask) -> void {
      if (d >= dist2[r][a][mask]) return;
      dist2[r][a][mask] = d;
      pq.push({-d, a, mask});
    };
    push(0, r, 0);
    while (pq.size() > 0) {
      auto [d, a, mask] = pq.top();
      pq.pop();
      if ((d = -d) != dist2[r][a][mask]) continue;
      for (int i = 0; i < (1 << K); i++) {
        if (mask & i) continue;
        push(d + dist[a][i], a, mask | i);
      }
      for (int b = 0; b < N; b++) {
        push(d + C[a][b], b, mask);
      }
    }
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int s, t;
    cin >> s >> t;
    s--, t--;

    i64 ans = INF;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < (1 << K); j++) {
        ans = min(ans, dist2[s][i][j] + dist2[t][i][j ^ ((1 << K) - 1)]);
      }
    }
    cout << ans << '\n';
  }
}
