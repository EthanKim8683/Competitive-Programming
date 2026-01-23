#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;
const i64 MOD = 9302023;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string S;
  cin >> S;

  int N = S.size();

  auto combine = [&](pair<int, i64> a, pair<int, i64> b) -> pair<int, i64> {
    if (b < a) {
      swap(a, b);
    }
    auto [l1, c1] = a;
    auto [l2, c2] = b;
    if (l2 == l1) {
      (c1 += c2) %= MOD;
    }
    return {l1, c1};
  };

  vector<pair<int, i64>> dp(N + 1, {INF, 0});
  dp[0] = {0, 1};
  for (int i = 0; i < N; i++) {
    auto [l, c] = dp[i];
    for (auto s : (string[]) {"zero", "one", "two", "three", "four", "five",
                              "six", "seven", "eight", "nine"}) {
      if (i + s.size() <= N) {
        if (S.substr(i, s.size()) == s) {
          dp[i + s.size()] = combine(dp[i + s.size()], {l + 1, c});
        }
      }
    }
    dp[i + 1] = combine(dp[i + 1], {l + 1, c});
  }
  auto [l, c] = dp[N];
  cout << l << '\n' << c;
}