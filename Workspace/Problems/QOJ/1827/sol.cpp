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

const int MAXX = 300;
const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  auto is_edge = [&](int i, int j) -> bool { return abs(i - j) <= 1; };

  vc dp(MAXX + 1, vi(MAXX + 1, INF));
  rep(i, 1, MAXX + 1) {
    rep(j, 1, MAXX + 1) {
      if (is_edge(i, j)) continue;
      vi grundy;
      rep(k, 1, i) { grundy.pb(dp[k][j]); }
      rep(k, 1, j) { grundy.pb(dp[i][k]); }
      sort(all(grundy));
      dp[i][j] = 0;
      for (auto e : grundy) {
        if (e != dp[i][j]) continue;
        dp[i][j]++;
      }
    }
  }

  int N;
  cin >> N;

  while (N--) {
    int X1, Y1, X2, Y2;
    cin >> X1 >> Y1 >> X2 >> Y2;

    auto is_winning = [&](int x1, int y1, int x2, int y2) -> bool {
      if (is_edge(x1, x2) and is_edge(y1, y2)) {
        return x1 != x2 and y1 != y2;
      } else if (is_edge(x1, x2)) {
        return true;
      } else if (is_edge(y1, y2)) {
        return true;
      } else {
        return (dp[x1][x2] ^ dp[y1][y2]) != 0;
      }
    };
    int ans = 0;
    rep(i, Y1 == Y2 and X2 < X1 ? X2 + 1 : 1, X1) {
      if (!is_winning(i, Y1, X2, Y2)) {
        ans++;
      }
    }
    rep(i, X1 == X2 and Y2 < Y1 ? Y2 + 1 : 1, Y1) {
      if (!is_winning(X1, i, X2, Y2)) {
        ans++;
      }
    }
    rep(i, Y1 == Y2 and X1 < X2 ? X1 + 1 : 1, X2) {
      if (!is_winning(X1, Y1, i, Y2)) {
        ans++;
      }
    }
    rep(i, X1 == X2 and Y1 < Y2 ? Y1 + 1 : 1, Y2) {
      if (!is_winning(X1, Y1, X2, i)) {
        ans++;
      }
    }
    cout << ans << '\n';
  }
}
