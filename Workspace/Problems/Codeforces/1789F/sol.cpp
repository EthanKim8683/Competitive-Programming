#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string S;
  cin >> S;

  int N = S.size();

  // If k is even, we pick a partition and find the LCS

  auto chmax = [&](int &a, int b) -> void { a = max(a, b); };

  int ans = 0;

  auto lcs = [&](string A, string B) -> int {
    int N = A.size(), M = B.size();
    vector dp(N + 1, vector<int>(M + 1, -INF));
    dp[0][0] = 0;
    for (int i = 0; i <= N; i++) {
      for (int j = 0; j <= M; j++) {
        if (i < N and j < M and A[i] == B[j]) {
          chmax(dp[i + 1][j + 1], dp[i][j] + 1);
        }
        if (i < N) {
          chmax(dp[i + 1][j], dp[i][j]);
        }
        if (j < M) {
          chmax(dp[i][j + 1], dp[i][j]);
        }
      }
    }
    return dp[N][M];
  };
  for (int i = 1; i < N; i++) {
    chmax(ans, 2 * lcs(S.substr(0, i), S.substr(i)));
  }
  cout << ans;
}
