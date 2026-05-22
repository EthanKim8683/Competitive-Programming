#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

#include "ethankim8683/combinatorics.hpp"
using namespace ethankim8683;

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

  int H, W;
  cin >> H >> W;

  if (H % 2 != 1) {
    cout << "0\n";
    exit(0);
  }

  if (W % 2 == 0) {
    // vc<mint> A(H + 1), B(H + 1);
    // rep(i, 0, H + 1) {
    //   A[i] = binom<mint>(H, i);
    //   B[H - i] = binom<mint>(H, i);
    // }
    // auto C = convolution(A, B);
    // mint ans = 0;
    // rep(i, -H, H + 1) {
    //   if (gcd(abs(i), W / 2) != 1) continue;
    //   ans += C[H + i];
    // }
    // cout << ans.val() << '\n';

    mint ans = 0;
    rep(i, 0, 2 * H + 1) {
      if (gcd(abs(i - (2 * H - i)), W) != 2) continue;
      ans += binom<mint>(2 * H, i);
    }
    cout << ans.val() << '\n';
  } else {
    mint ans = 0;
    rep(i, 0, H + 1) {
      if (gcd(abs(i - (H - i)), W) != 1) continue;
      ans += binom<mint>(H, i);
    }
    cout << ans.val() << '\n';
  }
}
