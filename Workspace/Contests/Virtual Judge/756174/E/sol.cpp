#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef pair<float, float> vec;

const int INF = 1e9;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // 50^4 dp, only go on required squares

  int N, K;
  cin >> N >> K;

  vc matrix(N, vi(N));
  for (auto &r : matrix) {
    for (auto &e : r) {
      cin >> e;
      e--;
    }
  }

  vc<vc<pii>> positions(K);
  rep(i, 0, N) {
    rep(j, 0, N) { positions[matrix[i][j]].eb(i, j); }
  }

  auto chmin = [&](int &a, int b) -> void { a = min(a, b); };

  vc dp(N, vi(N, INF));
  for (auto [i, j] : positions[0]) {
    dp[i][j] = 0;
  }
  rep(i, 0, K - 1) {
    for (auto [j, k] : positions[i]) {
      for (auto [l, m] : positions[i + 1]) {
        chmin(dp[l][m], dp[j][k] + abs(j - l) + abs(k - m));
      }
    }
  }
  int ans = INF;
  for (auto [i, j] : positions[K - 1]) {
    chmin(ans, dp[i][j]);
  }
  cout << (ans == INF ? -1 : ans);
}