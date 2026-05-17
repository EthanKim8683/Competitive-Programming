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

  int N;
  cin >> N;

  vc<pii> ranges(N);
  for (auto &[l, r] : ranges) {
    cin >> l >> r;
  }

  vc ps(3, vi(N + 2, 0));
  for (auto [l, r] : ranges) {
    int l2 = N - r, r2 = N - l;
    if (max(l, l2) <= min(r, r2)) {
      if (l < l2) {
        ps[0][l] += 1;
        ps[0][l2] -= 1;
        ps[1][l2] += 1;
        ps[1][r + 1] -= 1;
        ps[2][r + 1] += 1;
        ps[2][r2 + 1] -= 1;
      } else {
        ps[2][l2] += 1;
        ps[2][l] -= 1;
        ps[1][l] += 1;
        ps[1][r2 + 1] -= 1;
        ps[0][r2 + 1] += 1;
        ps[0][r + 1] -= 1;
      }
    } else {
      ps[0][l] += 1;
      ps[0][r + 1] -= 1;
      ps[2][l2] += 1;
      ps[2][r2 + 1] -= 1;
    }
  }
  rep(i, 0, 3) {
    rep(j, 0, N + 1) { ps[i][j + 1] += ps[i][j]; }
  }

  mint ans = 0;
  rep(i, 1, N + 1) {
    if (ps[0][i] + ps[1][i] + ps[2][i] != N) continue;
    ans += binom<mint>(ps[1][i], i - ps[0][i]);
  }
  cout << ans.val() << '\n';
}
