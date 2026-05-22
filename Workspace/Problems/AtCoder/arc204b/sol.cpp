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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // minimum number of operations is NK - (number of cycles)
  //
  // increase the number of cycles every operation
  //
  // swap i, j in same cycle
  //
  // maybe I can range dp?

  int N, K;
  cin >> N >> K;

  vi P(N * K);
  for (auto &e : P) {
    cin >> e;
    e--;
  }

  vc<bool> seen(N * K, false);
  vi domain;
  auto dfs = [&](auto self, int a) -> void {
    if (seen[a]) return;
    seen[a] = true;
    domain.pb(a);
    self(self, P[a]);
  };
  vc<vi> indices(N);
  int ans = 0;
  rep(i, 0, N * K) {
    if (seen[i]) continue;
    domain.clear();
    dfs(dfs, i);

    int n = sz(domain);

    // vc dp(n + 1, vi(n + 1, 0));
    // rep(i, 1, n + 1) {
    //   rep(j, 0, n + 1 - i) {
    //     chmax(dp[j][j + i], dp[j + 1][j + i]);
    //     chmax(dp[j][j + i], dp[j][j + i - 1]);
    //     rep(k, 1, i) { chmax(dp[j][j + i], dp[j][j + k] + dp[j + k][j + i]);
    //     } if (i >= 2 and abs(domain[j] - domain[j + i - 1]) % N == 0) {
    //       chmax(dp[j][j + i], dp[j + 1][j + i] + 1);
    //     }
    //   }
    // }
    // ans += dp[0][n];

    rep(i, 0, n) { indices[domain[i] % N].pb(i); }
    vc dp(n + 1, vi(n + 1, 0));
    for (int i = n; i >= 0; i--) {
      rep(j, i, n + 1) {
        if (i + 1 <= j) {
          chmax(dp[i][j], dp[i + 1][j]);
        }
        if (i <= j - 1) {
          chmax(dp[i][j], dp[i][j - 1]);
        }
        if (j < n) {
          for (auto k : indices[domain[j] % N]) {
            if (k <= j) continue;
            chmax(dp[i][k + 1], dp[i][j] + dp[j + 1][k + 1] + 1);
          }
        }
      }
    }
    ans += dp[0][n];
    for (auto e : domain) {
      indices[e % N].clear();
    }
  }
  cout << ans << '\n';
}
