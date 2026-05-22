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
const int MAXC = 300;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc C(N, vi(N));
  for (auto &r : C) {
    for (auto &e : r) {
      cin >> e;
      e--;
    }
  }

  vi colors;
  vc<bool> used(N, false);
  rep(i, 0, N) {
    rep(j, 0, N) {
      if (used[j]) continue;
      int c = MAXC;
      bool ok = true;
      rep(k, 0, N) {
        if (used[k]) continue;
        if (j == k) continue;
        if (c == MAXC) {
          c = C[j][k];
        } else {
          ok = ok and C[j][k] == c;
        }
      }
      if (ok) {
        used[j] = true;
        colors.pb(c);
        break;
      }
    }
  }

  vi fact(N + 1);
  fact[0] = 1;
  rep(i, 1, N + 1) { fact[i] = fact[i - 1] * i % MOD; }

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

  vc binom(N + 1, vi(N + 1));
  rep(i, 0, N + 1) {
    rep(j, 0, i + 1) {
      binom[i][j] = fact[i] * mod_inv(fact[j] * fact[i - j]) % MOD;
    }
  }

  reverse(all(colors));
  int ans = 0;
  rep(i, 0, N) {
    vi counts(MAXC, 0);
    rep(j, i + 1, N) { counts[colors[j]] += 1; }
    vc dp(MAXC + 1, vi(N + 1, 0));
    dp[0][1] = 1;
    rep(j, 0, MAXC) {
      rep(k, 0, N + 1) {
        rep(l, 0, counts[j] + 1) {
          (dp[j + 1][max(k, l + 1)] += dp[j][k] * binom[counts[j]][l]) %= MOD;
        }
      }
    }
    rep(j, 0, N + 1) { (ans += dp[MAXC][j] * j) %= MOD; }
  }
  cout << ans << '\n';
}
