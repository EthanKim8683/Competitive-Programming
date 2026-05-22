#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

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

const int MAXP = 1e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // x y
  // z w
  //
  // (x + z) - (y + w) = 0
  // (x + y) - (z + w) = 0
  //
  // x = z + w - y
  // (z + w - y + z) - (y + w) = 0
  // 2z - 2y = 0
  // z = y
  // x = w

  int N;
  cin >> N;

  vi P(N);
  for (auto &e : P) cin >> e;

  vc dp(N + 1, vc<mint>(2 * MAXP + 1, 0));
  dp[0][MAXP + 0] = 1;
  rep(i, 0, N) {
    rep(j, 0, 2 * MAXP + 1) {
      if (dp[i][j] == 0) continue;
      dp[i + 1][j - P[i]] += dp[i][j];
      dp[i + 1][j + P[i]] += dp[i][j];
    }
  }
  mint count = dp[N][MAXP];
  cout << (count * (count - 2)).val() << '\n';
}
