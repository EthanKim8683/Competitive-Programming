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

  vi A(N);
  for (auto &e : A) cin >> e;

  if (A[0] != 1) {
    cout << "0\n";
    exit(0);
  }

  vc<mint> dp(N + 1);
  dp[0] = 1;
  rep(i, 1, N + 1) { dp[i] = dp[i - 1] * (2 * i - 1); }

  mint ans = 1;
  int ktotal = 0;
  for (int l = 0, r; l < N; l = r) {
    for (r = l + 1; r < N and A[r] == A[l]; r++);
    int n = r - l;
    if (n % 2 == 0) {
      cout << "0\n";
      exit(0);
    }
    int k = (n - 1) / 2;
    ans *= dp[k] / fact<mint>(k);
    ktotal += k;
  }
  ans *= fact<mint>(ktotal);
  cout << ans.val() << '\n';
}
