#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  i64 L;
  cin >> N >> L;

  vector<pair<int, i64>> tiles(N);
  for (auto &[r, c] : tiles) {
    cin >> r >> c;
    r--, c--;
  }

  map<i64, int> masks;
  for (auto [r, c] : tiles) {
    masks[c] |= 1 << r;
  }

  auto chmin = [&](int &a, int b) -> void { a = min(a, b); };

  vector dp(1 << 2, INF);
  dp[0] = 0;
  for (auto [i, mask] : masks) {
    vector dp2(1 << 2, INF);
    if (mask == 3) {
      chmin(dp2[0], dp[0]);
      chmin(dp2[1], dp[2] + 1);
      chmin(dp2[2], dp[1] + 1);
    } else if (mask == 1) {
      if (i % 2 == 0) {
        chmin(dp2[0], dp[1]);
        chmin(dp2[2], dp[0]);
        chmin(dp2[0], dp[2] + 1);
        chmin(dp2[1], dp[0] + 1);
      } else {
        chmin(dp2[0], dp[2]);
        chmin(dp2[1], dp[0]);
        chmin(dp2[0], dp[1] + 1);
        chmin(dp2[2], dp[0] + 1);
      }
    } else if (mask == 2) {
      if (i % 2 == 0) {
        chmin(dp2[0], dp[2]);
        chmin(dp2[1], dp[0]);
        chmin(dp2[0], dp[1] + 1);
        chmin(dp2[2], dp[0] + 1);
      } else {
        chmin(dp2[0], dp[1]);
        chmin(dp2[2], dp[0]);
        chmin(dp2[0], dp[2] + 1);
        chmin(dp2[1], dp[0] + 1);
      }
    }
    dp = dp2;
  }
  int ans = dp[0];
  if (ans == INF) {
    cout << "no\n";
  } else {
    cout << ans << '\n';
  }
}
