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

const int MOD = 1e9 + 7;
const int MAXN = 2e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // number of ways to relabel vertices such that each vertex (besides vertex 0)
  // has exactly one edge with label less than the vertex's label
  //
  // rerooting DP?

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) { fact[i] = fact[i - 1] * i % MOD; }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    auto mod_pow = [&](int x, int y) -> int {
      int rv = 1;
      for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
        if (y & 1) {
          (rv *= x) %= MOD;
        }
      }
      return rv;
    };

    auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

    // auto dfs = [&](auto self, int a, int p) -> pii {
    //   int n = 1, m = 1;
    //   for (auto b : adj[a]) {
    //     if (b == p) continue;
    //     auto [n2, m2] = self(self, b, a);
    //     n += n2;
    //     (m *= m2) %= MOD;
    //     (m *= mod_inv(fact[n2])) %= MOD;
    //   }
    //   (m *= fact[n - 1]) %= MOD;
    //   return {n, m};
    // };
    // int ans = 0;
    // rep(i, 0, N) {
    //   auto [n, m] = dfs(dfs, i, -1);
    //   (ans += m) %= MOD;
    // }
    // (ans *= mod_inv(fact[N - 1])) %= MOD;
    // (ans *= mod_inv(fact[N])) %= MOD;
    // cout << ans << '\n';

    vc<pii> dp(N);
    auto dfs = [&](auto self, int a, int p) -> void {
      auto &[n, m] = dp[a];
      n = 1;
      m = 1;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
        auto [n2, m2] = dp[b];
        n += n2;
        (m *= m2) %= MOD;
        (m *= fact[n2 - 1]) %= MOD;
        (m *= mod_inv(fact[n2])) %= MOD;
      }
    };
    dfs(dfs, 0, -1);

    int ans = 0;
    vc<pii> dp2(N);
    auto dfs2 = [&](auto self, int a, int p) -> void {
      auto [n, m] = dp[a];
      if (p != -1) {
        auto [n2, m2] = dp2[a];
        n += n2;
        (m *= m2) %= MOD;
        (m *= fact[n2 - 1]) %= MOD;
        (m *= mod_inv(fact[n2])) %= MOD;
      }
      (ans += m * fact[n - 1]) %= MOD;
      for (auto b : adj[a]) {
        if (b == p) continue;
        auto [n2, m2] = dp[b];
        (m *= fact[n2]) %= MOD;
        (m *= mod_inv(fact[n2 - 1])) %= MOD;
        (m *= mod_inv(m2)) %= MOD;
        n -= n2;
        dp2[b] = {n, m};
        self(self, b, a);
        n += n2;
        (m *= m2) %= MOD;
        (m *= fact[n2 - 1]) %= MOD;
        (m *= mod_inv(fact[n2])) %= MOD;
      }
    };
    dfs2(dfs2, 0, -1);
    (ans *= mod_inv(fact[N - 1])) %= MOD;
    (ans *= mod_inv(fact[N])) %= MOD;
    cout << ans << '\n';
  }
}


