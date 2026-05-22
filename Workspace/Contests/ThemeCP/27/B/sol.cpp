#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

#include "ethankim8683/combinatorics.hpp"
using namespace ethankim8683;

using mint = modint1000000007;

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
    int N, X;
    cin >> N >> X;

    vc<mint> add, mul;
    rep(i, 0, N) {
      char symbol;
      int y;
      cin >> symbol >> y;

      if (symbol == '+') {
        add.pb(y);
      } else if (symbol == '-') {
        add.pb(-y);
      } else if (symbol == 'x') {
        mul.pb(y);
      } else {
        mul.pb(mint(1) / y);
      }
    }

    mint base = X;
    for (auto e : mul) {
      base *= e;
    }

    if (sz(add) == 0) {
      cout << base.val() << '\n';
      continue;
    }

    vc dp(sz(mul) + 1, vc<mint>(sz(mul) + 1, 0));
    dp[0][0] = 1;
    rep(i, 0, sz(mul)) {
      rep(j, 0, i + 1) {
        dp[i + 1][j] += dp[i][j];
        dp[i + 1][j + 1] += dp[i][j] * mul[i];
      }
    }

    vc<mint> evprod(sz(mul) + 1);
    rep(i, 0, sz(mul) + 1) {
      evprod[i] = dp[sz(mul)][i] / binom<mint>(sz(mul), i);
    }

    vc<mint> evsprod(N);
    rep(i, 0, N) {
      evsprod[i] = 0;
      rep(j, 0, min(i, sz(mul)) + 1) {
        evsprod[i] += evprod[j] * binom<mint>(i, j) *
                      binom<mint>((N - 1) - i, sz(mul) - j) /
                      binom<mint>(N - 1, sz(mul));
      }
    }

    mint evsum = 0;
    for (auto e : add) {
      evsum += e / N;
    }

    mint ans = base;
    rep(i, 0, N) { ans += evsum * evsprod[N - (i + 1)]; }
    cout << ans.val() << '\n';
  }
}
