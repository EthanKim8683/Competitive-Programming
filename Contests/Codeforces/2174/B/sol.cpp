#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vc<int> sizes;
    int i0 = 0;
    vi C = {A[i0]};
    rep(i, 1, N) {
      if (A[i] > A[i0]) {
        C.pb(A[i]);
        sizes.pb(i - i0);
        i0 = i;
      }
    }
    sizes.pb(N - i0);

    vc dp(sz(C) + 1, vc(K + 1, vi(K + 1, -INF)));
    dp[0][0][0] = 0;
    rep(i, 0, sz(C)) {
      rep(j, 0, K + 1) {
        rep(k, 0, K + 1) { chmax(dp[i + 1][j][k], dp[i][j][k] + k * sizes[i]); }
        int best = *max_element(all(dp[i][j]));
        rep(k, 0, min(C[i], K - j) + 1) {
          chmax(dp[i + 1][j + k][k], best + k * sizes[i]);
        }
      }
    }
    int ans = 0;
    rep(i, 0, K + 1) {
      rep(j, 0, K + 1) { chmax(ans, dp[sz(C)][i][j]); }
    }
    cout << ans << '\n';
  }
}
