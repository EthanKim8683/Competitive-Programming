#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N, M;
  if (argc > 1) {
    N = 500;
    M = 4e5;
  } else {
    cin >> N >> M;
  }

  vector<tuple<int, int, int>> ops(M);
  if (argc > 1) {
    for (auto &[x, y, z] : ops) {
      do {
        x = rng() % N;
        y = rng() % N;
      } while (x == y);
      z = rng() % ((int) 1e5 + 1);
    }
  } else {
    for (auto &[x, y, z] : ops) {
      cin >> x >> y >> z;
      x--, y--;
    }
  }

  vector<vector<pair<int, int>>> adj(N);
  for (auto [x, y, z] : ops) {
    adj[y].emplace_back(x, z);
  }

  vector dist(N, vector<i64>(N, INF));
  priority_queue<tuple<i64, int, int>> pq;
  auto push = [&](int s, int a, i64 d) -> void {
    if (d >= dist[s][a]) return;
    dist[s][a] = d;
    pq.emplace(-d, s, a);
  };
  for (int i = 0; i < N; i++) {
    push(i, i, 0);
  }
  while (pq.size() > 0) {
    auto [d, s, a] = pq.top();
    pq.pop();
    if ((d = -d) != dist[s][a]) continue;
    for (auto [b, w] : adj[a]) {
      push(s, b, d + w);
    }
  }

  int Q;
  if (argc > 1) {
    Q = 1000;
  } else {
    cin >> Q;
  }

  while (Q--) {
    int K;
    if (argc > 1) {
      K = rng() % ((int) 1e9 + 1);
    } else {
      cin >> K;
    }

    vector<int> A(N);
    if (argc > 1) {
      for (auto &e : A) {
        e = rng() % ((int) 1e9 + 1);
      }
    } else {
      for (auto &e : A) cin >> e;
    }

    vector<i64> dist2(N, INF);
    for (int i = 0; i < N; i++) {
      dist2[i] = min(dist2[i], (i64) A[i]);
      for (auto [b, w] : adj[i]) {
        dist2[b] = min(dist2[b], (i64) A[i] + w);
      }
    }

    vector<bool> ans(N, false);
    for (int i = 0; i < N; i++) {
      vector<i64> dist3 = dist2;
      dist3[i] = min(dist3[i], (i64) A[i] - K);
      for (auto [b, w] : adj[i]) {
        dist3[b] = min(dist3[b], (i64) A[i] - K + w);
      }
      for (int j = 0; j < N; j++) {
        ans[j] = ans[j] or A[i] - K + dist[i][j] < dist3[j];
      }
    }
    for (auto e : ans) {
      cout << e;
    }
    cout << '\n';
  }
}
