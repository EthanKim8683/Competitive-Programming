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

const int INF = 1e18;

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

    vi B(N);
    for (auto &e : B) cin >> e;

    vc dp(N + 1, vi(3, -INF));
    rep(i, 0, N) {
      chmax(dp[i + 1][0], B[i] - 1);
      rep(j, 0, 3) {
        chmax(dp[i + 1][j], dp[i][j] - 1);
        if (j + 1 < 3) {
          chmax(dp[i + 1][j + 1], dp[i][j] + B[i] - 1);
        }
      }
    }
    cout << dp[N][3 - 1] + 1 << '\n';
  }
}
