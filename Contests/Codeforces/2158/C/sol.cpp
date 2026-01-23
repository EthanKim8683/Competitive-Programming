#pragma GCC optimize("Ofast,unroll-loops")
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

    vi B(N);
    for (auto &e : B) cin >> e;

    if (K % 2 == 0) {
      int ps = 0, ans = -INF;
      for (auto e : A) {
        chmax(ps, 0);
        ps += e;
        chmax(ans, ps);
      }
      cout << ans << '\n';
    } else {
      vc dp(N + 1, vi(2, -INF));
      dp[0][0] = 0;
      rep(i, 0, N) {
        chmax(dp[i + 1][0], A[i]);
        chmax(dp[i + 1][0], dp[i][0] + A[i]);
        chmax(dp[i + 1][1], A[i] + B[i]);
        chmax(dp[i + 1][1], dp[i][0] + A[i] + B[i]);
        chmax(dp[i + 1][1], dp[i][1] + A[i]);
      }
      int ans = -INF;
      rep(i, 0, N + 1) { chmax(ans, dp[i][1]); }
      cout << ans << '\n';
    }
  }
}
