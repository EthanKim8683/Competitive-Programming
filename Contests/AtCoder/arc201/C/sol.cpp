#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
#include "atcoder/segtree.hpp"
using namespace atcoder;

using mint = modint998244353;

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

  // covered, not covered

  int N;
  cin >> N;

  vc<string> S(N);
  for (auto &e : S) cin >> e;

  vc<array<int, 2>> adj;
  vc<bool> is_end;
  vi size;
  vc<mint> dp;
  auto make = [&]() -> int {
    int rv = sz(adj);
    adj.pb({-1, -1});
    is_end.pb(false);
    size.pb(0);
    dp.pb(0);
    return rv;
  };
  make();
  auto insert = [&](string s) -> void {
    auto dfs = [&](auto self, int a, int i) -> void {
      if (i < sz(s)) {
        int j = s[i] - 'A';
        if (adj[a][j] == -1) {
          adj[a][j] = make();
        }
        self(self, adj[a][j], i + 1);
      } else {
        is_end[a] = true;
      }
      size[a] = 0;
      dp[a] = 1;
      for (auto b : adj[a]) {
        if (b == -1) {
          dp[a] = 0;
        } else {
          size[a] += size[b];
          dp[a] *= dp[b];
        }
      }
      if (is_end[a]) {
        size[a] += 1;
        dp[a] += mint(2).pow(size[a] - 1);
      }
    };
    dfs(dfs, 0, 0);
  };
  for (auto e : S) {
    insert(e);
    cout << dp[0].val() << '\n';
  }
}
