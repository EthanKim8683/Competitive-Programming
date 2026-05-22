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
const int HALF = 5e8 + 4;
const int LOGN = 27;
const int MAXN = 200000;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vi fib(LOGN);
  fib[0] = 1;
  fib[1] = 1;
  rep(i, 2, LOGN) { fib[i] = fib[i - 2] + fib[i - 1]; }

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) { fact[i] = fact[i - 1] * i % MOD; }

  int N;
  cin >> N;

  int ans = 0, pow = 1;
  rep(i, 1, N + 1) {
    (pow *= N) %= MOD;
    (ans += pow) %= MOD;
  }
  vc dp(min(N, LOGN) + 1, vc(N + 1, vc(2, vi(2, 0))));
  dp[0][0][1][1] = 1;
  rep(i, 0, min(N, LOGN)) {
    rep(j, 0, N + 1) {
      rep(k, 0, 2) {
        rep(l, 0, 2) { (dp[i + 1][j][l][0] += dp[i][j][k][l]) %= MOD; }
      }
      if (j + fib[i] <= N) {
        rep(k, 0, 2) {
          rep(l, 0, 2) {
            (dp[i + 1][j + fib[i]][k][1] += dp[i + 1][j][k][l]) %= MOD;
          }
        }
        rep(k, 0, 2) {
          (ans += MOD - dp[i + 1][j][0][k] * fact[i + 1] % MOD * HALF % MOD) %=
              MOD;
          (ans += MOD - dp[i + 1][j][1][k] * fact[i + 1] % MOD) %= MOD;
        }
      }
    }
  }
  cout << ans << '\n';
}
