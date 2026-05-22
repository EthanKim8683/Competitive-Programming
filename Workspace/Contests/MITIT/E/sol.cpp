#ifndef L
// #pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "ethankim8683/utils.hpp"

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

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  int size(int x) { return -e[find(x)]; }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b], e[b] = a;
    return true;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vc<tuple<int, int, int>> tiles(N);
  for (auto &[x, y, t] : tiles) {
    cin >> x >> y >> t;
  }

  vi order(N);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> bool { return tiles[a] < tiles[b]; });

  UF uf(N);
  map<int, int> prev;
  for (auto e : order) {
    auto [x, y, t] = tiles[e];
    if (prev.contains(x) and get<2>(tiles[prev[x]]) == t) {
      uf.join(e, prev[x]);
    }
    prev[x] = e;
  }

  vc<map<int, pii>> adj(sz(tiles));
  prev.clear();
  for (auto e : order) {
    auto [x, y, t] = tiles[e];
    if (prev.contains(y) and get<2>(tiles[prev[y]]) == t) {
      int p = prev[y], a = uf.find(e), b = uf.find(p);
      adj[a][b] = adj[b][a] = {p, e};
    }
    prev[y] = e;
  }

  vc<bool> seen(N, false);
  auto dfs = [&](auto self, int a, int p) -> void {
    assert(!seen[a]);
    seen[a] = true;

    vi be;
    for (auto [b, e] : adj[a]) {
      if (b == p) continue;

      if (seen[b]) {
        be.pb(b);
        continue;
      }

      self(self, b, a);
    }
    for (auto e : be) {
      adj[a].erase(e);
    }
  };
  rep(i, 0, N) {
    if (i != uf.find(i)) continue;
    if (seen[i]) continue;
    dfs(dfs, i, -1);
  }

  fill(all(seen), false);
  vi color(N, 0);
  auto dfs2 = [&](auto self, int a, int p) -> int {
    if (seen[a]) return 0;
    seen[a] = true;

    int rv = uf.size(a) % 2;
    for (auto [b, e] : adj[a]) {
      if (b == p) continue;

      int w = self(self, b, a);
      if (w == 1) {
        auto [a2, b2] = e;
        color[a2] ^= 1;
        color[b2] ^= 1;
      }
      rv ^= w;
    }
    return rv;
  };
  rep(i, 0, N) {
    if (i != uf.find(i)) continue;
    if (dfs2(dfs2, i, -1) == 1) {
      cout << "NO\n";
      exit(0);
    }
  }

  vc<pii> ans;

  prev.clear();
  for (auto e : order) {
    if (color[e] != 0) continue;

    auto [x, y, t] = tiles[e];
    if (prev.contains(x)) {
      ans.eb(e, prev[x]);
      prev.erase(x);
    } else {
      prev[x] = e;
    }
  }

  prev.clear();
  for (auto e : order) {
    if (color[e] != 1) continue;

    auto [x, y, t] = tiles[e];
    if (prev.contains(y)) {
      ans.eb(e, prev[y]);
      prev.erase(y);
    } else {
      prev[y] = e;
    }
  }

  cout << "YES\n";
  for (auto [a, b] : ans) {
    cout << a + 1 << ' ' << b + 1 << '\n';
  }

  viz([&]() -> void {
    rep(i, 0, N) {
      auto [x, y, t] = tiles[i];
      DrawText(to_string(t).c_str(), 100 + x * 10, 100 + y * 10, 12,
               color[i] ? RED : WHITE);
    }
  });
}
