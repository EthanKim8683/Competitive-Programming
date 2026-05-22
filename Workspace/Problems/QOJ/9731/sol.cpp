#ifndef L
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 1:49
  // thinking done: 1:55
  // target impl time: 25 min
  // initial impl done: 2:08

  // strongly connected components
  // contiguous ranges are fuzzy with each other
  // find ranges

  int T;
  cin >> T;

  while (T--) {
    int N, K, Q;
    cin >> N >> K >> Q;

    vc lists(K, vi(N));
    for (auto &r : lists) {
      for (auto &e : r) {
        cin >> e;
        e--;
      }
    }

    vc<vi> adj(N), radj(N);
    for (auto r : lists) {
      rep(i, 0, N - 1) {
        int a = r[i], b = r[i + 1];
        adj[a].pb(b);
        radj[b].pb(a);
      }
    }

    vc<bool> seen(N, false);
    vi order;
    auto dfs = [&](auto self, int a) -> void {
      if (seen[a]) return;
      seen[a] = true;

      for (auto b : adj[a]) {
        self(self, b);
      }
      order.pb(a);
    };
    rep(i, 0, N) { dfs(dfs, i); }
    reverse(all(order));

    vi root(N, -1);
    auto dfs2 = [&](auto self, int a, int r) -> void {
      if (root[a] != -1) return;
      root[a] = r;

      for (auto b : radj[a]) {
        self(self, b, r);
      }
    };
    for (auto e : order) {
      dfs2(dfs2, e, e);
    }

    auto triangle = [&](int n) -> int { return n * (n - 1) / 2; };

    vc<vc<pii>> ranges(K);
    vc ps(K, vi(N + 1, 0));
    rep(i, 0, K) {
      for (int l = 0; l < N;) {
        int r = l;
        while (r < N and root[lists[i][r]] == root[lists[i][l]]) {
          r++;
        }

        ranges[i].eb(l, r);
        ps[i][l + 1] += triangle(r - l);

        l = r;
      }

      rep(j, 0, N) { ps[i][j + 1] += ps[i][j]; }
    }

    int v = 0;
    while (Q--) {
      int id, l, r;
      cin >> id >> l >> r;

      id = (id + v) % K + 1;
      l = (l + v) % N + 1;
      r = (r + v) % N + 1;
      id--, l--;

      v = ps[id][r] - ps[id][l];

      auto it = lower_bound(all(ranges[id]), pii{l, -1});
      if (it != ranges[id].begin()) {
        auto [l2, r2] = *prev(it);
        if (l2 < l and r2 <= r) {
          v += triangle(r2 - l);
        } else if (l2 < l and r < r2) {
          v += triangle(r - l);
        }
      }

      it = lower_bound(all(ranges[id]), pii{r, -1});
      if (it != ranges[id].begin()) {
        auto [l2, r2] = *prev(it);
        if (l <= l2 and r < r2) {
          v -= triangle(r2 - l2);
          v += triangle(r - l2);
        }
      }

      cout << v << '\n';
    }
  }
}
