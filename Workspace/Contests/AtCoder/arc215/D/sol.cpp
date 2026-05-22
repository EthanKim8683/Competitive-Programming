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

  // if S is non-decreasing, each mod 2 group is non-decreasing
  //
  // does this uniquely give S? no. look at base sum
  //
  // let's look at all pairs of non-decreasing seqs, then see what base sums we
  // can add
  //
  // equal final vs diff final
  //
  // just exclude equal final?
  // can we fft? no. see mod
  //
  // N/2+1, (N+1)/2

  int N, M;
  cin >> N >> M;

  auto snb = [&](int n, int k) -> mint {
    if (n == 0 and k == 0) return 1;
    return binom<mint>(n + k - 1, k - 1);
  };
  mint ans = 0;
  {
    mint sum = 0;
    rep(i, 0, M + 1) { sum += snb(i, (N + 1) / 2 - 1); }
    rep(i, 0, M + 1) { ans += snb(i, N / 2 + 1 - 1) * (M + 1 - i) * sum; }
  }
  {
    rep(i, 0, M + 1) {
      ans += snb(M, N / 2 + 1) * snb(i, (N + 1) / 2 - 1) * (M - i);
    }
  }
  cout << ans.val() << '\n';
}
