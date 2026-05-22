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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // naively: dsu

  int N;
  cin >> N;

  vc<vc<signed>> adj(N);
  rep(i, 0, N - 1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  vc<string> A(N);
  for (auto &e : A) cin >> e;

  vc dist(N, vi(N));
  vc inner(N, vc<pii>(N, {-1, -1}));
  rep(i, 0, N) {
    auto dfs = [&](auto self, int a, int p, int r, int d) -> void {
      dist[i][a] = d;
      if (d > 1) {
        inner[i][a] = {r, p};
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, r, d + 1);
      }
    };
    dist[i][i] = 0;
    for (auto b : adj[i]) {
      dfs(dfs, b, i, b, 1);
    }
  }

  vc<pii> pairs;
  rep(i, 0, N) {
    rep(j, 0, N) { pairs.eb(i, j); }
  }
  sort(all(pairs), [&](pii a, pii b) -> bool {
    auto key = [&](pii x) -> int {
      auto [a, b] = x;
      return dist[a][b];
    };
    return key(a) < key(b);
  });

  for (int i = sz(pairs) - 1; i >= 0; i--) {
    auto [a, b] = pairs[i];
    if (A[a][b] != '1') continue;
    if (inner[a][b] == pii{-1, -1}) continue;
    auto [c, d] = inner[a][b];
    A[c][d] = '1';
  }

  dsu uf(N);
  rep(i, 0, N) {
    rep(j, 0, N) {
      if (A[i][j] != '1') continue;
      uf.merge(i, j);
    }
  }

  vc is_pal(N, vc<bool>(N));
  for (auto [a, b] : pairs) {
    if (inner[a][b] == pii{-1, -1}) {
      is_pal[a][b] = uf.same(a, b);
    } else {
      auto [c, d] = inner[a][b];
      is_pal[a][b] = is_pal[c][d] and uf.same(a, b);
    }
  }

  int ans = 0;
  rep(i, 0, N) {
    rep(j, 0, N) {
      if (!is_pal[i][j]) continue;
      ans += 1;
    }
  }
  cout << ans << '\n';
}
