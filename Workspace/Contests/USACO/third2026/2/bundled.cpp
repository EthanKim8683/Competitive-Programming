#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

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

  // dist -> flower
  //
  // can only pass through flower at that distance

  int T;
  cin >> T;

  while (T--) {
    int N, M, K, L;
    cin >> N >> M >> K >> L;

    vi S(K);
    for (auto &e : S) {
      cin >> e;
      e--;
    }

    vi D(L);
    for (auto &e : D) {
      cin >> e;
      e--;
    }

    vc<vi> adj(N);
    rep(i, 0, M) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vi dist(N, INF);
    queue<int> q;
    auto push = [&](int a, int d) -> void {
      if (d >= dist[a]) return;
      dist[a] = d;
      q.push(a);
    };
    push(0, 0);
    while (sz(q) > 0) {
      int a = q.front();
      q.pop();
      for (auto b : adj[a]) {
        push(b, dist[a] + 1);
      }
    }

    bool ok = true;
    vi by_dist(N, -1);
    for (auto e : S) {
      ok = ok and by_dist[dist[e]] == -1;
      by_dist[dist[e]] = e;
    }
    if (!ok) {
      cout << string(N - 1, '0') << '\n';
      continue;
    }

    int dmax = 0;
    for (auto e : S) {
      chmax(dmax, dist[e]);
    }

    vi dist2(N, INF), order;
    vc<vi> parents(N);
    auto push2 = [&](int a, int d, int p) -> void {
      if (d > dist2[a]) return;
      if (by_dist[d] != -1) {
        if (a != by_dist[d]) return;
      }
      if (d < dist2[a]) {
        dist2[a] = d;
        parents[a].clear();
        q.push(a);
      }
      if (p != -1) {
        parents[a].pb(p);
      }
    };
    push2(0, 0, -1);
    while (sz(q) > 0) {
      int a = q.front();
      q.pop();
      order.pb(a);
      for (auto b : adj[a]) {
        push2(b, dist2[a] + 1, a);
      }
    }
    reverse(all(order));
    vc<bool> ans(N, false);
    for (auto e : D) {
      ans[e] = dist2[e] == dist[e] and dist[e] >= dmax;
    }
    for (auto e : order) {
      for (auto e2 : parents[e]) {
        ans[e2] = ans[e2] or ans[e];
      }
    }
    rep(i, 1, N) { cout << ans[i]; }
    cout << '\n';
  }
}


