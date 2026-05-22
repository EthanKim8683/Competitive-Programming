#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 11:56
  // thinking done: 12:05
  // target impl time: 15 min
  // initial impl done: 12:14

  // int N = 1e5;
  // vc<double> ps(N + 1, 0);
  // rep(i, 1, N) {
  //   ps[0] += 1.L / i;
  //   ps[i] -= 1.L / i;
  // }
  // rep(i, 0, N) { ps[i + 1] += ps[i]; }
  // cerr << *max_element(all(ps)) << '\n';

  int N;
  cin >> N;

  vc<vi> adj(N);
  rep(i, 1, N) {
    int p;
    cin >> p;
    p--;
    adj[p].pb(i);
  }

  vi facts(N + 1);
  facts[0] = 1;
  rep(i, 1, N + 1) { facts[i] = facts[i - 1] * i % MOD; }

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

  auto dfs = [&](auto self, int a, int d) -> vi {
    vi dp(d + 2, 0);
    rep(i, 0, d + 2) { dp[i] = mod_inv(facts[i]); }
    for (auto b : adj[a]) {
      auto dp2 = self(self, b, d + 1);
      vi dp3(d + 2, 0);
      rep(i, 0, d + 2) {
        rep(j, 0, d + 2 - i) { (dp3[i + j] += dp[i] * dp2[j]) %= MOD; }
      }
      dp = dp3;
    }
    return {dp.begin() + 1, dp.end()};
  };
  cout << dfs(dfs, 0, 0)[0] * facts[N] % MOD << '\n';
}
