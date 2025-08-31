#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector C(N, vector<int>(N));
  for (auto &r : C) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vector ps(N + 1, vector<i64>(N + 1, 0));
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      ps[i][j] =
          ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + C[i - 1][j - 1];
    }
  }
  auto query = [&](int l1, int r1, int l2, int r2) -> i64 {
    return ps[r1][r2] - ps[l1][r2] - ps[r1][l2] + ps[l1][l2];
  };

  auto rate = [&](int l, int r) -> i64 {
    return query(0, l, l, r) + query(r, N, l, r);
  };

  vector dp(N + 1, vector<pair<i64, int>>(N + 1, {INF, -1}));
  auto dfs = [&](auto self, int l, int r) -> i64 {
    if (dp[l][r].first != INF) {
      return dp[l][r].first;
    }

    if (r - l <= 1) {
      dp[l][r] = {0, l};
      return dp[l][r].first;
    }

    for (int i = l; i < r; i++) {
      i64 sum1 = self(self, l, i), sum2 = self(self, i + 1, r);
      dp[l][r] = min(dp[l][r], {sum1 + sum2 + rate(l, i) + rate(i + 1, r), i});
    }
    return dp[l][r].first;
  };
  dfs(dfs, 0, N);

  vector<int> ans(N);
  auto dfs2 = [&](auto self, int l, int r, int p) -> void {
    if (r - l == 0) return;

    auto [sum, m] = dp[l][r];
    ans[m] = p;
    self(self, l, m, m);
    self(self, m + 1, r, m);
  };
  dfs2(dfs2, 0, N, -1);

  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
}
