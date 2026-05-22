#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  // on regular game:
  //
  // states by endpoints and length
  //
  // if (A, A, N-1) wins, player 1 loses
  //
  // player 2 always wins
  //
  // grundy(A, A, K) = 1
  // grundy(A, B, K) = 0
  //
  // any player can play any move, it's still a winning game for player 2

  // N = 100;
  // vector dp(N + 1, vector(2, vector<int>(2, 0)));
  // for (int i = 1; i <= N; i++) {
  //   for (int j = 0; j < 2; j++) {
  //     for (int k = 0; k < 2; k++) {
  //       vector<int> S;
  //       for (int l = 0; l < 2; l++) {
  //         for (int m = 0; m <= i - 1; m++) {
  //           if (m == 0 and l == j) continue;
  //           if (m == i - 1 and l == k) continue;
  //           S.push_back(dp[m][j][l] ^ dp[i - 1 - m][l][k]);
  //         }
  //       }
  //       sort(S.begin(), S.end());
  //       int mex = 0;
  //       for (auto e : S) {
  //         if (mex == e) {
  //           mex++;
  //         }
  //       }
  //       dp[i][j][k] = mex;
  //     }
  //   }
  // }
  // for (int i = 1; i <= N; i++) {
  //   cout << dp[i][0][1] << ' ';
  // }

  vector<mint> dp(N + 1);
  for (int i = 1; i <= N - 1; i += 2) {
    dp[i] = 2 * N * binom<mint>(i + 1, N - 1 - i);
  }
  for (int i = N - 1; i >= 1; i--) {
    dp[i - 1] += dp[i] * i;
  }
  cout << dp[0].val();
}
