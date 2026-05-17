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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // ps - psmin < u
  // psmin > ps - u
  //
  // dp on i and x

  int N, L, R;
  cin >> N >> L >> R;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi B(N);
  for (auto &e : B) cin >> e;

  vi ps1(N + 1), ps2(N + 1);
  ps1[0] = ps2[0] = 0;
  rep(i, 0, N) {
    ps1[i + 1] = ps1[i] + A[i];
    ps2[i + 1] = ps2[i] + B[i];
  }

  auto lt = [&](int u) -> int {
    vc dp(N + 1, vi(N + 1, 0));
    dp[0][0] = 1;
    rep(i, 0, N + 1) {
      rep(j, 0, i + 1) {
        if (ps2[j] - ps1[i] <= ps2[N] - ps1[N] - u) {
          dp[i][j] = 0;
        }
        if (i + 1 <= N) {
          (dp[i + 1][j] += dp[i][j]) %= MOD;
        }
        if (j + 1 <= i) {
          (dp[i][j + 1] += dp[i][j]) %= MOD;
        }
      }
    }
    return dp[N][N];
  };
  cout << (lt(R + 1) + MOD - lt(L)) % MOD << '\n';
}
