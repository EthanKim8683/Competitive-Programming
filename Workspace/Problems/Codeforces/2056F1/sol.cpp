#include <bits/stdc++.h>

#include "ethankim8683/combinatorics.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int K, M;
    cin >> K >> M;

    string N;
    cin >> N;

    int O = count(N.begin(), N.end(), '1');
    vector dp(O + 1, vector<int>(O + 1, 0));
    dp[0][O] = 1;
    int ans = 0;
    for (int i = 0; i <= O; i++) {
      if (i + 1 <= O) {
        for (int j = 1; j <= O - i; j++) {
          for (int k = 0; k <= j - 1; k++) {
            (dp[i + 1][j - 1 - k] +=
             dp[i][j] * lucas_binom<int>(j - 1, k, 2)) %= 2;
          }
        }
      }

      if (i >= 1) {
        for (int j = 0; j < M; j++) {
          if (dp[i][0] * lucas_binom<int>(j, i - 1, 2) % 2 == 1) {
            ans ^= j;
          }
        }
      }
    }
    cout << ans << '\n';
  }
}
