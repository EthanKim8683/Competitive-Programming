#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, S, T;
  cin >> N >> M >> S >> T;
  S--, T--;

  vector<vector<int>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<pair<int, int>> from_S(N, {INF, -1}), from_T(N, {INF, -1});
  queue<int> q;
  auto push = [&](vector<pair<int, int>> &dist, pair<int, int> d,
                  int a) -> void {
    if (d >= dist[a]) return;
    dist[a] = d;
    q.push(a);
  };
  push(from_S, {0, -1}, S);
  while (q.size() > 0) {
    int a = q.front();
    q.pop();
    if (a == T) continue;
    for (auto b : adj[a]) {
      push(from_S, {from_S[a].first + 1, a}, b);
    }
  }
  push(from_T, {0, -1}, T);
  while (q.size() > 0) {
    int a = q.front();
    q.pop();
    if (a == S) continue;
    for (auto b : adj[a]) {
      push(from_T, {from_T[a].first + 1, a}, b);
    }
  }
  vector<bool> used(N, false);
  for (int a = T; a != -1; a = from_S[a].second) {
    used[a] = true;
  }
  int ans = INF;
  for (int i = 0; i < N; i++) {
    if (used[i]) continue;
    ans = min(ans, from_S[T].first + from_S[i].first + from_T[i].first);
  }
  set<int> seen;
  for (int i = 0; i < N; i++) {
    if (used[i]) continue;
    int d = from_S[i].first;
    if (d == INF) continue;
    if (seen.contains(d)) {
      ans = min(ans, 2 * (from_S[T].first + 2 * d));
    }
    seen.insert(d);
  }
  seen.clear();
  for (int i = 0; i < N; i++) {
    if (used[i]) continue;
    int d = from_T[i].first;
    if (d == INF) continue;
    if (seen.contains(d)) {
      ans = min(ans, 2 * (from_S[T].first + 2 * d));
    }
    seen.insert(d);
  }
  cout << (ans >= INF ? -1 : ans);
}
