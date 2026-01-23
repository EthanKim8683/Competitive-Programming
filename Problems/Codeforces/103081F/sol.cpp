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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 8:34
  // thinking done: 8:39
  // target impl time: 5 min
  // initial impl done: 8:43

  int R, N, M;
  cin >> R >> N >> M;
  R--;

  vc dp(N + 1, vi(N + 1, 0));
  dp[0][0] = 1 % M;
  rep(i, 0, N) {
    rep(j, 0, i + 1) {
      (dp[i + 1][j + 1] += dp[i][j]) %= M;
      if (i != R) {
        if (j >= 1) {
          (dp[i + 1][j] += dp[i][j] * j) %= M;
        }
        if (j >= 2) {
          (dp[i + 1][j - 1] += dp[i][j] * (j * (j - 1) / 2)) %= M;
        }
      }
    }
  }
  cout << dp[N][1] << '\n';
}
