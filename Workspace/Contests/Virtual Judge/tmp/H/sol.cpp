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

  int L, R;
  cin >> L >> R;

  auto lt = [&](int x) -> int {
    vi digits;
    for (int i = x; i != 0; i /= 10) {
      digits.pb(i % 10);
    }
    reverse(all(digits));

    vc dp(sz(digits) + 1, vc(9 + 1, vi(2, 0)));
    dp[0][0][1] = 1;
    rep(i, 0, sz(digits)) {
      if (i < sz(digits) - 1) {
        rep(j, 0, 2) {
          rep(k, 0, 9 + 1) {
            if (j == 1 and k > digits[i]) continue;
            dp[i + 1][k][j == 1 and k == digits[i] ? 1 : 0] += dp[i][0][j];
          }
        }
      }
      rep(j, 0, 9 + 1) {
        rep(k, 0, 2) {
          rep(l, 0, j) {
            if (k == 1 and l > digits[i]) continue;
            dp[i + 1][j][k == 1 and l == digits[i] ? 1 : 0] += dp[i][j][k];
          }
        }
      }
    }
    int ans = 0;
    rep(i, 0, 9 + 1) { ans += dp[sz(digits)][i][0]; }
    return ans;
  };
  cout << lt(R + 1) - lt(L) << '\n';
}
