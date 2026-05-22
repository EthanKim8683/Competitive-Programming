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

  if (N > 50) exit(0);

  vector<mint> dp(N + 1, 0);
  dp[1] = 1;
  for (int i = 2; i <= N; i++) {
    vector dpi(i + 1, vector<mint>(i + 1, 0));
    dpi[0][0] = 1;
    for (int j = 0; j < i; j++) {
      for (int k = 0; k <= j; k++) {
        for (int l = 1; l < i and j + l <= i; l++) {
          dpi[j + l][k + 1] += dpi[j][k] / fact<mint>(l);
        }
      }
    }
    for (int j = 1; j <= i; j++) {
      dp[i] += dpi[i][j] * fact<mint>(i) / fact<mint>(j);
    }
  }
  for (auto e : dp) {
    cerr << e.val() << ' ';
  }
  cout << (2 * dp[N]).val();
}
