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

  int R, C;
  cin >> R >> C;

  vc X(R, vi(C));
  for (auto &r : X) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  auto sign = [&](int x) -> int { return (x > 0) - (x < 0); };

  auto is_monotonic = [&](int x1, int x2, int x3) -> bool {
    return sign(x2 - x1) == 0 or sign(x3 - x2) == 0 or
           sign(x3 - x2) == sign(x2 - x1);
  };

  vc is_row_monotonic(R, vc<bool>(1 << C));
  rep(i, 0, R) {
    rep(j, 1, 1 << C) {
      int k1 = -1, k2 = -1, k3 = -1;
      bool ok = true;
      rep(k, 0, C) {
        if (~j >> k & 1) continue;
        tie(k1, k2, k3) = make_tuple(k2, k3, k);
        if (k1 == -1 or k2 == -1 or k3 == -1) continue;
        ok = ok and is_monotonic(X[i][k1], X[i][k2], X[i][k3]);
      }
      is_row_monotonic[i][j] = ok;
    }
  }

  vc masks(R, vc(R, vi(R, 0)));
  rep(i, 0, R) {
    rep(j, i, R) {
      rep(k, j + 1, R) {
        rep(l, 0, C) {
          if (!is_monotonic(X[i][l], X[j][l], X[k][l])) continue;
          masks[i][j][k] |= 1 << l;
        }
      }
    }
  }

  int ans = 0;
  rep(i, 0, R) {
    vc dp(R, vi(1 << C, 0));
    rep(j, 1, 1 << C) {
      if (!is_row_monotonic[i][j]) continue;
      dp[i][j] += 1;
    }
    rep(j, i, R) {
      rep(k, 1, (1 << C)) {
        if (is_row_monotonic[j][k]) continue;
        dp[j][k] = 0;
      }
      rep(k, 1, (1 << C)) { ans += dp[j][k]; }
      rep(k, j + 1, R) {
        int mask = masks[i][j][k];
        for (int l = mask; l != 0; l = (l - 1) & mask) {
          dp[k][l] += dp[j][l];
        }
      }
    }
  }
  cout << ans << '\n';
}
