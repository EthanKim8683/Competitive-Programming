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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K;
  cin >> N >> K;

  vc<pair<char, int>> cards(N);
  for (auto &[s, v] : cards) {
    cin >> s >> v;
  }

  vc dp(N + 1, vi(N + 1, -INF));
  dp[0][0] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      auto [s, v] = cards[i];
      chmax(dp[i + 1][j], dp[i][j]);
      if (s == 'a') {
        chmax(dp[i + 1][j + 1], dp[i][j] + v);
      } else {
        chmax(dp[i + 1][j + 1], dp[i][j] * v);
      }
    }
  }
  for (int i = 0; i + 1 <= N; i++) {
    cerr << dp[N][i + 1] - dp[N][i] << ' ';
  }
}
