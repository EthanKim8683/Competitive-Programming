#ifndef L
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

const int MAXN = 50;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N + 1);
    for (auto &e : A) cin >> e;

    // only the last cycle matters

    int k = *max_element(A.begin() + 1, A.end()) - 1, f = 0;
    rep(i, 1, N + 1) {
      if (A[i] > k) {
        f++;
      } else {
        A[0] -= k - A[i];
      }
    }
    if (A[0] < 0) {
      cout << "0\n";
      continue;
    }

    vc dp(N + 1, vc<mint>(N + 1, 0));
    dp[0][0] = 1;
    rep(i, 0, N) {
      rep(j, 0, i + 1) {
        if (j == f or A[0] - (i - j) > 0) {
          dp[i + 1][j] += dp[i][j];
        }
        if (j + 1 <= f) {
          dp[i + 1][j + 1] += dp[i][j];
        }
      }
    }
    mint ans = dp[N][f];
    auto fact = [&](int n) -> mint {
      mint rv = 1;
      for (int i = 1; i <= n; i++) {
        rv *= i;
      }
      return rv;
    };
    ans *= fact(f);
    ans *= fact(N - f);

    cout << ans.val() << '\n';
  }
}
