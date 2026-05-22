#include <bits/stdc++.h>

#include <algorithm>
#include <numeric>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> P(N);
  for (auto &e : P) cin >> e;

  vector<int> C(N);
  for (auto &e : C) cin >> e;

  vector<vector<int>> dp(N + 1);
  for (int i = 0; i < N; i++) {
    auto it = lower_bound(dp[C[i]].begin(), dp[C[i]].end(), P[i]);
    if (it == dp[C[i]].end()) {
      dp[C[i]].push_back(P[i]);
    } else {
      *it = P[i];
    }
  }
  i64 ans = accumulate(C.begin(), C.end(), 0ll);
  for (int i = 1; i <= N; i++) {
    ans -= (i64) i * dp[i].size();
  }
  cout << ans;
}