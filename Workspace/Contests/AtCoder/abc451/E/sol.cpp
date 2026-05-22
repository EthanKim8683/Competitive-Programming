#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/dsu.hpp"
using namespace atcoder;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // mst??

  int N;
  cin >> N;

  vc<tuple<int, int, int>> edges(N);
  rep(i, 0, N) {
    rep(j, i + 1, N) {
      int w;
      cin >> w;
      edges.eb(w, i, j);
    }
  }

  sort(all(edges));
  dsu d(N);
  vc<vc<pii>> adj(N);
  for (auto [w, u, v] : edges) {
    if (d.same(u, v)) continue;
    adj[u].eb(v, w);
    adj[v].eb(u, w);
    d.merge(u, v);
  }

  vc dist(N, vi(N, INF));
  rep(i, 0, N) {
    priority_queue<pii> pq;
    auto push = [&](int a, int d) -> void {
      if (d >= dist[i][a]) return;
      dist[i][a] = d;
      pq.emplace(-d, a);
    };
    push(i, 0);
    while (sz(pq) > 0) {
      auto [d, a] = pq.top();
      pq.pop();
      if ((d = -d) != dist[i][a]) continue;
      for (auto [b, w] : adj[a]) {
        push(b, d + w);
      }
    }
  }

  bool ans = true;
  for (auto [w, u, v] : edges) {
    ans = ans and dist[u][v] == w;
  }
  cout << (ans ? "Yes" : "No") << '\n';
}
