#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> D(N);
  for (auto &e : D) cin >> e;

  auto f = [&](int N, int D0) -> mint {
    if (D0 == 0) return N == 1;
    return fact<mint>(N - 2) / fact<mint>(D0 - 1) * fact<mint>(D0);
  };

  // [j,:] - subtree size
  // [:,k] - subtree outdegree sum
  vector dp(N + 1, vector<mint>(N + 1, 0));
  dp[0][0] = 1;
  mint ans = f(N, D[0]);
  for (int i = N - 1; i > 0; i--) {
    for (int M = 1 + D[i]; M <= N; M++) {
      // j+1 = M
      // k+D[i] = M-1
      ans += dp[M - 1][M - 1 - D[i]] * f(M, D[i]) * f(N - (M - 1), D[0]);
    }

    for (int j = N - 1; j >= 0; j--) {
      for (int k = 0; k + D[i] <= N; k++) {
        dp[j + 1][k + D[i]] += dp[j][k];
      }
    }
  }
  for (auto e : D) {
    ans /= fact<mint>(e);
  }
  cout << ans.val();
}
