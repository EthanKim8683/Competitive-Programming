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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int K;
  cin >> K;

  mint ans = 0;
  rep(i, 2, K) {
    rep(j, 2, K) {
      int k = K - (i + j);
      if (!(k >= 2)) continue;
      vi X = {i, j, k};
      sort(all(X));
      ans += (mint) (X[0] + X[1]) * (i - 1) * (j - 1) * (k - 1);
    }
  }
  cout << ans.val() << '\n';
}
