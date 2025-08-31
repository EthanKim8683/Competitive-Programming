#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int P;
  cin >> P;

  auto chmin = [&](auto &a, auto b) -> void { a = min(a, b); };
  vector<pair<i64, i64>> dp(P + 1, {INF, -INF});
  dp[0] = {0, 0};
  for (int i = 0; i <= P; i++) {
    for (int j = 0; j * (j - 1) / 2 <= i; j++) {
      auto [a, b] = dp[i - j * (j - 1) / 2];
      chmin(dp[i], make_pair(a + j, b - a * j));
    }
  }
  auto [a, b] = dp[P];
  cout << a << ' ' << -b;
}
