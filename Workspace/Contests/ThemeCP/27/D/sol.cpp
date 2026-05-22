#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/convolution.hpp"
#include "atcoder/modint.hpp"
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

  // fft

  // each segment stores:
  // - parity of y's
  // - multiplier of x
  //
  // evil math...

  int T;
  cin >> T;

  while (T--) {
    int N, X, Y;
    cin >> N >> X >> Y;

    string S;
    cin >> S;

    // mint countl = 1;
    // for (auto e : S) {
    //   if (e == '?') {
    //     countl *= 2;
    //   }
    // }
    // mint ans = 0, contrib = 0, countr = 1;
    // for (int i = N - 1; i >= 0; i--) {
    //   if (S[i] == '0') {
    //     contrib += countr;
    //     ans += countl * X * contrib;
    //     contrib *= 1;
    //   } else if (S[i] == '1') {
    //     contrib += countr;
    //     ans += countl * Y * contrib;
    //     contrib *= -1;
    //   } else {
    //     countl /= 2;
    //     contrib += countr;
    //     ans += countl * (X + Y) * contrib;
    //     contrib = 0;
    //     countr *= 2;
    //   }
    // }
    // cout << ans.val() << '\n';

    // mint n = 1, dp1 = 0, dp2 = 0;
    // for (auto e : S) {
    //   mint dp3;
    //   if (e == '0') {
    //     dp3 = n * X + 2 * dp2 - dp1;
    //   } else if (e == '1') {
    //     dp3 = n * Y + dp1;
    //   } else {
    //     dp3 = n * (X + Y) + 2 * dp2;
    //     n *= 2;
    //   }
    //   tie(dp1, dp2) = pair{dp2, dp3};
    // }
    // cout << dp2.val() << '\n';
  }
}
