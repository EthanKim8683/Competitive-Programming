#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

#include "ethankim8683/combinatorics.hpp"

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

using mint = static_modint<676767677>;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // number of iterations to find each value
  //
  // so get value v
  //
  // we only go left if we're looking for < v
  //
  // we only go right if we're looking for > v
  //
  // whenever we "find" a value, use information about how many less and how
  // many more to count number of sequences
  //
  // must increase after last lt and before m, and after m and before first gt
  //
  // must have M - 1 total increases

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    // M-1 stars, N bars

    auto snb = [&](int n, int k) -> mint { return binom<mint>(n + k, k); };

    mint ans = 0;
    auto dfs = [&](auto self, int l, int r, int l2, int r2, int d) -> void {
      if (l > r) return;
      int m = (l + r) / 2;
      ans += d * snb(M - 1, N);
      if (l2 != -1) {
        // l2+1, m
        // m-l2
        ans -= d * snb(M - 1, N - (m - l2));
      }
      if (r2 != -1) {
        // m+1, r2
        // r2-m
        ans -= d * snb(M - 1, N - (r2 - m));
      }
      if (l2 != -1 and r2 != -1) {
        ans += d * snb(M - 1, N - (r2 - l2));
      }
      self(self, m + 1, r, m, r2, d + 1);
      self(self, l, m - 1, l2, m, d + 1);
    };
    dfs(dfs, 0, N - 1, -1, -1, 1);
    cout << ans.val() << '\n';
  }
}
