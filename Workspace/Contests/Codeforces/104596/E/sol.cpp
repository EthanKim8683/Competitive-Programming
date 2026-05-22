#pragma GCC optimize("trapv")
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
typedef vector<int> vi;

int dp[505][505][11];
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int r, c, n;
  cin >> r >> c >> n;

  vc<vi> board(r, vi(c));
  vc<vi> pass(r, vi(c));
  rep(i, 0, r) rep(j, 0, c) { cin >> board[i][j]; }

  rep(i, 1, r - 1) rep(j, 1, c - 1) {
    int up = board[i - 1][j];
    int down = board[i + 1][j];
    int left = board[i][j - 1];
    int right = board[i][j + 1];
    int curr = board[i][j];
    int q[] = {up, down, left, right, curr};
    if (std::any_of(all(q), [](int x) { return x < 0; })) {
      continue;
    }

    pass[i][j] = curr < up && curr < down && curr > left && curr > right;
  }

  constexpr int inf = 1e16;
  rep(j, 0, c) {
    rep(i, 0, r) {
      rep(p, 0, n + 1) { dp[i][j][p] = inf; }
    }
  }
  rep(i, 0, r) {
    if (board[i][0] != -1) dp[i][0][0] = board[i][0];
  }

  rep(j, 0, c - 1) {
    rep(i, 0, r) {
      rep(p, 0, n + 1) {
        if (dp[i][j][p] != inf) {
          int curr = dp[i][j][p];
          // try all possible moves
          rep(q, -1, 2) {
            int newR = i + q;
            if (newR >= 0 && newR < r && board[newR][j + 1] != -1) {
              // try moving
              int cost = curr + board[newR][j + 1];
              bool isPass = pass[newR][j + 1];
              int pp = p + isPass;
              if (pp <= n) {
                dp[newR][j + 1][pp] = min(dp[newR][j + 1][pp], cost);
              }
            }
          }
        }
      }
    }
  }

  int best = inf;
  rep(i, 0, r) best = min(best, dp[i][c - 1][n]);
  if (best == inf) {
    cout << "impossible\n";
  } else {
    cout << best << endl;
  }
}