#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> P(N);
  for (auto &e : P) cin >> e, e--;

  // we are the smallest number we haven't used

  vector<int> index(N);
  for (int i = 0; i < N; i++) {
    index[P[i]] = i;
  }

  auto chmin = [&](int &a, int b) -> void { a = min(a, b); };
  vector dp(N + 1, vector<int>(1 << K, INF));
  dp[0][0] = 0;
  fenwick_tree<int> ft(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < (1 << K); j++) {
      int mv = i - __builtin_popcount(j);
      if (mv < 0) continue;

      auto inv = [&](int v) -> int {
        int rv = ft.sum(index[v] + 1, N);
        for (int k = max(i - K, 0); k < mv; k++) {
          if (index[k] > index[v]) {
            rv++;
          }
        }
        for (int k = 0; k < K; k++) {
          if (~j >> k & 1) continue;
          int vk = mv + 1 + k;
          if (vk < N and index[vk] > index[v]) {
            rv++;
          }
        }
        return rv;
      };

      chmin(dp[i + 1][j >> (__builtin_ctz(~j) + 1)], dp[i][j] + inv(mv));

      for (int k = 0; k < K; k++) {
        if (j >> k & 1) continue;
        int v = mv + 1 + k;
        if (v < N) {
          chmin(dp[i + 1][j | 1 << k], dp[i][j] + inv(v));
        }
      }
    }

    if (i - K >= 0) {
      ft.add(index[i - K], 1);
    }
  }
  cout << dp[N][0];
}
