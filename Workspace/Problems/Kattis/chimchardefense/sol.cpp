#ifndef U
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

const int MAXH = 5000;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi H(N);
  for (auto &e : H) cin >> e;

  vi D(N);
  for (auto &e : D) cin >> e;

  vi C(N);
  for (auto &e : C) cin >> e;

  vc dp(N + 1, vi(MAXH + 1, -INF));
  dp[0][0] = 0;
  rep(i, 0, N) {
    int i2 = N - 1 - i;
    for (int j = MAXH; j >= 0; j--) {
      chmax(dp[i][min(j + D[i2], MAXH)], dp[i][j] - C[i2]);
    }
    for (int j = 0; j <= MAXH; j++) {
      chmax(dp[i + 1][j], dp[i][j] + min(H[i2], j));
    }
  }
  int ans = -INF;
  for (auto e : dp[N]) {
    chmax(ans, e);
  }
  cout << ans << '\n';
}
