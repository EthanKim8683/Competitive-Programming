#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"
#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector A(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N - i; j++) {
      cin >> A[i][j];
    }
  }

  dsu d(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N - i; j++) {
      if (A[i][j] != 1) continue;
      for (int k = i; k + 1 <= i + j; k++) {
        d.merge(k, k + 1);
      }
    }
  }

  vector<pair<int, int>> ranges(N);
  int t = 0;
  ranges[d.leader(0)].first = t;
  for (int i = 0; i + 1 < N; i++) {
    if (d.leader(i) != d.leader(i + 1)) {
      ranges[d.leader(i)].second = ranges[d.leader(i + 1)].first = ++t;
    }
  }
  ranges[d.leader(N - 1)].second = ++t;

  vector<int> check(t + 1, -1);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N - i; j++) {
      if (A[i][j] != 2) continue;
      int l = ranges[d.leader(i)].first, r = ranges[d.leader(i + j)].second;
      check[r] = max(check[r], l);
    }
  }

  vector dp(t + 1, vector<mint>(t + 1, 0));
  dp[1][0] = 2;
  for (int i = 1; i <= t; i++) {
    for (int j = 0; j <= check[i]; j++) {
      dp[i][j] = 0;
    }

    if (i + 1 <= t) {
      for (int j = 0; j < i; j++) {
        dp[i + 1][i] += dp[i][j];
        dp[i + 1][j] += dp[i][j];
      }
    }
  }
  mint ans = 0;
  for (auto e : dp[t]) {
    ans += e;
  }
  cout << ans.val();
}
