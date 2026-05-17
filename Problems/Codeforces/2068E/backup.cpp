#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  // vector<pair<int, int>> edges(M);
  // vector<vector<int>> adj(N);
  // for (auto &[s, t] : edges) {
  //   cin >> s >> t;
  //   s--, t--;
  //   adj[s].push_back(t);
  //   adj[t].push_back(s);
  // }

  // vector<int> dist(N, 0);
  // for (int i = 0; i < M; i++) {
  //   auto [s, t] = edges[i];
  //   vector<int> dist2(N, INF);
  //   queue<int> q;
  //   auto push = [&](int a, int d) -> void {
  //     if (d >= dist2[a]) return;
  //     dist2[a] = d;
  //     q.push(a);
  //   };
  //   push(N - 1, 0);
  //   while (q.size() > 0) {
  //     int a = q.front();
  //     q.pop();
  //     for (auto b : adj[a]) {
  //       if (pair{a, b} == pair{s, t}) continue;
  //       if (pair{b, a} == pair{s, t}) continue;
  //       push(b, dist2[a] + 1);
  //     }
  //   }
  //   for (int j = 0; j < N; j++) {
  //     dist[j] = max(dist[j], dist2[j]);
  //   }
  // }

  // auto check = [&](int x) -> bool {
  //   vector<int> dist2(N, INF);
  //   queue<int> q;
  //   auto push = [&](int a, int d) -> void {
  //     if (d >= dist2[a]) return;
  //     dist2[a] = d;
  //     q.push(a);
  //   };
  //   push(0, 0);
  //   while (q.size() > 0) {
  //     int a = q.front();
  //     q.pop();
  //     if (dist[a] + dist2[a] >= x) continue;
  //     for (auto b : adj[a]) {
  //       push(b, dist2[a] + 1);
  //     }
  //   }
  //   return dist[N - 1] + dist2[N - 1] >= x;
  // };
  // int l = 0, r = 2 * N;
  // while (l < r) {
  //   int m = l + (r - l + 1) / 2;
  //   check(m) ? l = m : r = m - 1;
  // }
  // cout << l << '\n';

  vector<vector<int>> adj(N);
  for (int i = 0; i < M; i++) {
    int s, t;
    cin >> s >> t;
    s--, t--;
    adj[s].push_back(t);
    adj[t].push_back(s);
  }

  vector<int> dist(N), order;
  queue<int> q;
  auto push = [&](int a, int d) -> void {
    if (d >= dist[a]) return;
    dist[a] = d;
    order.push_back(a);
    q.push(a);
  };
  push(N - 1, 0);
  while (q.size() > 0) {
    int a = q.front();
    q.pop();
    for (auto b : adj[a]) {
      push(b, dist[a] + 1);
    }
  }

  // two paths from two edges exiting current node
  //
  // one is cut and returns, while the other reaches the sink
  //
  //

  // if you don't cut anything, you can't do better than the cheapest child
  //
  // if you do cut it, you can't do better than all the other shortest paths

  reverse(order.begin(), order.end());
  vector<int> cost(N, INF);
  for (auto a : order) {
  }
}
