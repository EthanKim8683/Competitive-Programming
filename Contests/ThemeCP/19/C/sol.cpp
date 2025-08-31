#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int P1;
  i64 T1;
  cin >> P1 >> T1;

  int P2;
  i64 T2;
  cin >> P2 >> T2;

  int H, S;
  cin >> H >> S;

  // h + s * c - p, c = # of shoots, p = total power

  auto chmin = [&](i64 &a, i64 b) -> void { a = min(a, b); };
  vector<i64> dp(H + 1, INF);
  dp[H] = 0;
  i64 ans = INF;
  for (int i = H; i > 0; i--) {
    bool go = true;
    for (int j = 0; go; j++) {
      go = false;
      {
        i64 t = T1 * j, k = t / T2, p = j * P1 + k * P2 - S * (j + k - 1);
        if (j >= 1 and k >= 1 and p > 0) {
          chmin(i - p <= 0 ? ans : dp[i - p], dp[i] + t);
        }
        go = go or i - p > 0;
      }
      {
        i64 t = T2 * j, k = t / T1, p = j * P2 + k * P1 - S * (j + k - 1);
        if (j >= 1 and k >= 1 and p > 0) {
          chmin(i - p <= 0 ? ans : dp[i - p], dp[i] + t);
        }
        go = go or i - p > 0;
      }
    }
    chmin(ans, dp[i] + ((i - 1) / (P1 - S) + 1) * T1);
    chmin(ans, dp[i] + ((i - 1) / (P2 - S) + 1) * T2);
  }
  cout << ans;
}
