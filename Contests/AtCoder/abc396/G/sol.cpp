#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int H, W;
  cin >> H >> W;

  vector<string> A(H);
  for (auto &e : A) cin >> e;

  vector<int> masks(H, 0);
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      masks[i] |= (A[i][j] - '0') << j;
    }
  }

  vector dp(1 << W, vector<int>(W + 1, 0));
  for (auto e : masks) {
    dp[e][0]++;
  }
  for (int i = 0; i < W; i++) {
    vector dp2(1 << W, vector<int>(W + 1, 0));
    for (int j = 0; j < (1 << W); j++) {
      for (int k = 0; k <= i; k++) {
        dp2[j ^ 1 << i][k + 1] += dp[j][k];
        dp2[j][k] += dp[j][k];
      }
    }
    dp = dp2;
  }

  int ans = INF;
  for (int i = 0; i < (1 << W); i++) {
    int sum = 0;
    for (int j = 0; j <= W; j++) {
      sum += min(j, W - j) * dp[i][j];
    }
    ans = min(ans, sum);
  }
  cout << ans;
}
