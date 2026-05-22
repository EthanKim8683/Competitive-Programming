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

  int N, M, P;
  cin >> N >> M >> P;

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= P; y; y >>= 1, (x *= x) %= P) {
      if (y & 1) {
        (rv *= x) %= P;
      }
    }
    return rv;
  };

  if (N % 2 == 1 and M % 2 == 1) {
    cout << 1 << '\n';
    exit(0);
  } else if (N % 2 == 1) {
    cout << mod_pow(M / 2 + 1, N / 2) << '\n';
    exit(0);
  } else if (M % 2 == 1) {
    cout << mod_pow(N / 2 + 1, M / 2) << '\n';
    exit(0);
  }

  vc dp(2, vc(1 << (N / 2), vi(N / 2 + 1, 0)));
  rep(i, 0, N / 2 + 1) { dp[0][0][i] = 1; }
  rep(i, 0, M) {
    if (i % 2 == 0) {
      rep(j, 0, N / 2) {
        rep(k, 0, 1 << (N / 2)) {
          if (k >> j & 1) {
            rep(l, 0, N / 2 + 1) {
              (dp[i % 2][k][l] += dp[i % 2][k ^ 1 << j][l]) %= P;
            }
          }
        }
      }
    }

    rep(j, 0, 1 << (N / 2)) {
      rep(k, 0, N / 2 + 1) {
        if (k - 1 >= 0 and (~j >> (k - 1) & 1)) {
          dp[i % 2][j][k] = 0;
        }
      }
    }

    if (i + 1 < M) {
      rep(j, 0, 1 << (N / 2)) {
        rep(k, 0, N / 2 + 1) {
          rep(l, 0, N / 2 + 1) {
            int m = j ^ ((1 << (N / 2)) - 1), n = 0;
            n |= (m & ((1 << l) - 1)) >> 1 & (j & ~((1 << k) - 1));
            n |= (m & ~((1 << l) - 1)) << 1 & (j & ((1 << k) - 1));
            if (n == 0 or (i + 1) % 2 == 0) {
              (dp[(i + 1) % 2][m | n][l] += dp[i % 2][j][k]) %= P;
            }
          }
        }
      }
    }

    if (i + 1 < M) {
      rep(j, 0, 1 << (N / 2)) {
        rep(k, 0, N / 2 + 1) { dp[i % 2][j][k] = 0; }
      }
    }
  }
  int ans = 0;
  rep(i, 0, 1 << (N / 2)) {
    rep(j, 0, N / 2 + 1) { (ans += dp[(M - 1) % 2][i][j]) %= P; }
  }
  cout << ans << '\n';
}
