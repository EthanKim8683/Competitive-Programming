#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

#include "ethankim8683/combinatorics.hpp"
using namespace ethankim8683;

using mint = modint1000000007;

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

  // if ((is 1) + (number of descendant ops)) % 2 == 1, do op
  //
  // cost is max of both children
  //
  // binom(n, k)

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    // binom(i, j) = binom(i-1, j-1) + binom(i-1, j)
    //
    //   \sum_{j=0}^{K-1} binom(i, j) + \sum_{j=0}^K binom(i, j)
    // = \sum_{j=0}^K binom(i+1, j)
    //
    //   (\sum_{j=0}^{K-1} binom(i, j) + binom(i, K-1)) / 2
    // = \sum_{j=0}^{K-1} binom(i-1, j)

    mint ans = 0, sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    rep(i, 0, K + 1) { sum1 += binom<mint>(0, i); }
    rep(i, 0, K) { sum2 += binom<mint>(N - 1, i); }
    rep(i, 0, K) { sum3 += binom<mint>(0, i); }
    rep(i, 0, K - 1) { sum4 += binom<mint>(N - 1, i); }
    rep(i, 0, N) {
      mint c = num_binary_trees<mint>(i) * num_binary_trees<mint>(N - 1 - i);
      ans += c * sum1 * binom<mint>(N - 1 - i, K);
      sum1 = 2 * sum1 - binom<mint>(i, K);
      ans += c * binom<mint>(i, K) * sum2;
      sum2 = (sum2 + binom<mint>(N - 1 - (i + 1), K - 1)) / 2;
      ans += c * sum3 * binom<mint>(N - 1 - i, K - 1);
      sum3 = 2 * sum3 - binom<mint>(i, K - 1);
      ans += c * binom<mint>(i, K - 1) * sum4;
      sum4 = (sum4 + binom<mint>(N - 1 - (i + 1), K - 2)) / 2;
    }
    cout << ans.val() << '\n';
  }
}
