#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/algebra.hpp"

using namespace std;
using namespace atcoder;

using u32 = unsigned;
using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N - 1);
  for (auto &e : A) cin >> e;

  vector<map<int, int>> counts(N - 1);
  map<int, int> P;
  for (int i = 0; i < N - 1; i++) {
    for (auto p : factorize((u32) A[i])) {
      counts[i][p]++;
      P[p]++;
    }
  }

  mint ans = 1;
  for (auto [p, count] : P) {
    vector<mint> pows(count + 1);
    pows[0] = 1;
    for (int i = 1; i <= count; i++) {
      pows[i] = pows[i - 1] * p;
    }

    vector dp(N, vector(count + 1, vector<mint>(2, 0)));
    for (int i = 0; i <= count; i++) {
      dp[0][i][i == 0] = pows[i];
    }
    for (int i = 0; i < N - 1; i++) {
      for (int j = 0; j <= count; j++) {
        for (int k = 0; k < 2; k++) {
          if (counts[i][p] > 0 and counts[i][p] <= j) {
            int j_ = j - counts[i][p];
            dp[i + 1][j_][k or j_ == 0] += dp[i][j][k] * pows[j_];
          }
          int j_ = j + counts[i][p];
          if (j_ <= count) {
            dp[i + 1][j_][k or j_ == 0] += dp[i][j][k] * pows[j_];
          }
        }
      }
    }
    mint sum = 0;
    for (int i = 0; i <= count; i++) {
      sum += dp[N - 1][i][true];
    }
    ans *= sum;
  }
  cout << ans.val();
}
