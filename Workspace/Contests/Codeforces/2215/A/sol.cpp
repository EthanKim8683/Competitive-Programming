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

  // always mod p after

  int T;
  cin >> T;

  while (T--) {
    int N, K, P, Q;
    cin >> N >> K >> P >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi ps1(N + 1), ps2(N + 1);
    ps1[0] = ps2[0] = 0;
    rep(i, 0, N) {
      ps1[i + 1] = ps1[i] + A[i] % P;
      ps2[i + 1] = ps2[i] + A[i] % Q % P;
    }

    vc dp(N + 1, vi(2, INF));
    dp[0][0] = 0;
    rep(i, 0, N) {
      rep(j, 0, 2) {
        chmin(dp[i + 1][j],
              dp[i][j] + min(ps1[i + 1] - ps1[i], ps2[i + 1] - ps2[i]));
        if (i + K <= N) {
          chmin(dp[i + K][1],
                dp[i][j] + min(ps1[i + K] - ps1[i], ps2[i + K] - ps2[i]));
        }
      }
    }
    cout << dp[N][1] << '\n';
  }
}
