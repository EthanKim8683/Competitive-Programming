#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  auto chmax = [&](i64 &a, i64 b) -> void { a = max(a, b); };
  vector<i64> dp(2, -INF);
  dp[1] = 0;
  for (int i = 0; i < N; i++) {
    chmax(dp[i % 2], dp[1 - i % 2] + A[i]);
  }
  cout << dp[1 - N % 2];
}
