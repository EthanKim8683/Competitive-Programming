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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    auto query = [&](int k) -> vi {
      cout << "? " << k + 1 << endl;

      int q;
      cin >> q;

      vi path(q);
      for (auto &e : path) {
        cin >> e;
        e--;
      }
      return path;
    };

    auto answer = [&](vc<pii> edges) -> void {
      cout << "! " << sz(edges) << endl;
      for (auto [u, v] : edges) {
        cout << u + 1 << ' ' << v + 1 << endl;
      }
    };

    vc<set<int>> adj(N);
    vc<bool> complete(N, false);
    int k = 1;
    vi path0 = {0};
    while (true) {
      auto path = query(k);
      if (sz(path) == 0) break;

      rep(i, 0, sz(path0)) {
        if (i >= sz(path) or path0[i] != path[i]) {
          complete[path0[i]] = true;
        }
      }

      rep(i, 0, sz(path) - 1) { adj[path[i]].insert(path[i + 1]); }

      auto count_paths = [&](int r) -> int {
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

        vi dp(N, 0);
        dp[r] = 1;
        for (auto e : order) {
          for (auto b : adj[e]) {
            dp[b] += dp[e];
          }
        }
        return accumulate(all(dp), 0ll);
      };

      int dk = 1;
      rep(i, 0, sz(path)) {
        if (complete[path[i]]) {
          dk = count_paths(path[i]);
          break;
        }
      }
      k += dk;

      path0 = path;
    }

    vc<pii> edges;
    rep(i, 0, N) {
      for (auto e : adj[i]) {
        edges.eb(i, e);
      }
    }
    answer(edges);
  }
}
