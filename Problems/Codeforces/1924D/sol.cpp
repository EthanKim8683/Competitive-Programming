#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // vector dp(2 * 2e3 + 1, vector<mint>(2e3 + 1, 0));
  // dp[0][0] = 1;
  // for (int i = 0; i <= 2 * 2e3; i += 2) {
  //   for (int j = 0; j <= i / 2; j++) {
  //     for (int k = 2; i + k <= 2 * 2e3; k += 2) {
  //       dp[i + k][j + 1] += dp[i][j] * num_balanced_bracket_seqs<mint>(k -
  //       2);
  //     }
  //   }
  // }
  // for (int i = 1; i <= 2e3; i++) {
  //   for (int j = 1; j <= i; j++) {
  //     if (dp[2 * i][j] != num_composite_balanced_bracket_seqs<mint>(2 * i,
  //     j)) {
  //       cerr << i << ' ' << j << endl;
  //     }
  //   }
  // }

  vector cache1(2e3 + 1, vector<mint>(2e3 + 1));
  for (int i = 0; i <= 2e3; i++) {
    for (int j = 0; j <= i; j++) {
      cache1[i][j] = num_composite_balanced_bracket_seqs<mint>(2 * i, j);
    }
  }

  vector cache2(3 * 2e3 + 1, vector<mint>(2e3 + 1));
  cache2[0][0] = 1;
  for (int i = 1; i <= 3 * 2e3; i++) {
    cache2[i][0] = 1;
    for (int j = 1; j <= 2e3; j++) {
      cache2[i][j] = cache2[i - 1][j - 1] + cache2[i - 1][j];
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    if (K > N or K > M) {
      cout << 0 << '\n';
      continue;
    }

    mint ans = 0;
    for (int i = 1; i <= K; i++) {
      ans += cache1[K][i] * cache2[N + M - 2 * K + i][i];
    }
    cout << ans.val() << '\n';
  }
}
