#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, X, M;
  cin >> N >> X >> M;

  vector<int> fib(32, 0);
  fib[0] = 1;
  fib[1] = 1;
  for (int i = 2; i < fib.size(); i++) {
    fib[i] = fib[i - 1] + fib[i - 2];
  }

  vector dp(N + 1, vector<mint>(N * fib[X - 1] + 1, 0));
  dp[0][0] = 1;
  for (int i = 0; i < X; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k <= j * fib[i]; k++) {
        dp[j + 1][k + fib[i]] += dp[j][k];
      }
    }
  }

  mint ans = 0;
  for (int i = 0; i <= N * fib[X - 1]; i++) {
    // Zeckendorf's theorem
    auto find = [&](int x) -> int {
      int l = 0, r = fib.size() - 1;
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        fib[m] <= x ? l = m : r = m - 1;
      }
      return fib[l];
    };
    auto solve = [&](int x) -> int {
      int rv = 0;
      while (x > 0) {
        rv++;
        x -= find(x);
      }
      return rv;
    };

    if (solve(i) == M) {
      ans += dp[N][i];
    }
  }
  cout << ans.val();
}
