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

const int M = 30;
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

    // extra per lose

    if (K > M) {
      cout << __builtin_popcountll(N) - 1 + K << '\n';
      continue;
    }

    // fill up knock down

    // index, group size, moves

    vi B;
    rep(i, 0, 2 * M) { B.pb(N >> i & 1); }

    vc dp(2 * M + 1, vc(K + 1, vi(2, -INF)));
    dp[0][0][0] = 0;
    rep(i, 0, 2 * M) {
      rep(j, 0, K + 1) {
        if (B[i] == 0) {
          chmax(dp[i + 1][j][0], dp[i][j][0]);
          if (j + 2 <= K) {
            chmax(dp[i + 1][j + 2][1], dp[i][j][0] + 1);
          }
          chmax(dp[i + 1][j][0], dp[i][j][1]);
          if (j + 1 <= K) {
            chmax(dp[i + 1][j + 1][1], dp[i][j][1] + 1);
          }
        } else {
          chmax(dp[i + 1][j][0], dp[i][j][0]);
          if (j + 1 <= K) {
            chmax(dp[i + 1][j + 1][1], dp[i][j][0] + 1);
          }
          chmax(dp[i + 1][j][1], dp[i][j][1] + 1);
        }
      }
    }
    int ans = -INF;
    rep(i, 0, K + 1) {
      rep(j, 0, 2) { chmax(ans, dp[2 * M][i][j]); }
    }
    cout << ans << '\n';
  }
}
