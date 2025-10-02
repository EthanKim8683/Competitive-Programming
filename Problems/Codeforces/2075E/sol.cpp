#include <bits/stdc++.h>

#include "atcoder/modint"

using namespace std;
using namespace atcoder;
using mint = modint998244353;

const int K = 29;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, A, B;
    cin >> N >> M >> A >> B;

    // there can't be more than two distinct values in a nor b. let's call them
    // a_1, a_2, b_1 and b_2.
    //
    // if a_1 ^ a_2 != b_1 ^ b_2, then a_1 ^ b_1 != a_2 ^ b_2 and a_1 ^ b_2 !=
    // a_2 ^ b_1, in addition to a_1 ^ b_1 != a_2 ^ b_1 and a_1 ^ b_1 != a_1 ^
    // b_2, so a_1 ^ a_2 == b_1 ^ b_2 must hold true.

    // if (A > 2e3 or B > 2e3) {
    //   cout << '?' << '\n';
    //   continue;
    // }
    // map<int, int> counts1, counts2;
    // for (int i = 0; i <= A; i++) {
    //   for (int j = i + 1; j <= A; j++) {
    //     counts1[i ^ j]++;
    //   }
    // }
    // for (int i = 0; i <= B; i++) {
    //   for (int j = i + 1; j <= B; j++) {
    //     counts2[i ^ j]++;
    //   }
    // }
    // int x = 0;
    // for (auto [e, count1] : counts1) {
    //   x += count1;
    // }
    // mint ans = (mint) (A + 1) * (B + 1);
    // ans += (mint) (A + 1) * (B + 1) * B / 2 * (mint(2).pow(M) - 2);
    // ans += (mint) (B + 1) * (A + 1) * A / 2 * (mint(2).pow(N) - 2);
    // for (auto [e, count1] : counts1) {
    //   ans += (mint) count1 * counts2[e] * (mint(2).pow(N) - 2) *
    //          (mint(2).pow(M) - 2);
    // }
    // cout << ans.val() << '\n';

    // I get the feeling it's just digit dynamic programming

    auto get_digits = [&](int x) -> vector<int> {
      vector<int> digits(K, 0);
      for (int i = K - 1; x > 0; i--, x /= 2) {
        digits[i] = x % 2;
      }
      return digits;
    };

    auto digits1 = get_digits(A + 1), digits2 = get_digits(B + 1);

    // i: i
    // j: a_2 < A
    // k: b_2 < B
    // l: a_1 < a_2
    // m: b_1 < b_2
    // n: a_1
    // o: b_1
    // p: a_1 ^ a_2 = b_1 ^ b_2
    // q: a_2
    // r: b_2
    vector dp(K + 1, vector(2, vector(2, vector(2, vector<mint>(2, 0)))));
    dp[0][0][0][0][0] = 1;
    for (int i = 0; i < K; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          for (int l = 0; l < 2; l++) {
            for (int m = 0; m < 2; m++) {
              for (int n = 0; n < 2; n++) {
                for (int o = 0; o < 2; o++) {
                  for (int p = 0; p < 2; p++) {
                    int q = n ^ p, r = o ^ p;
                    if (!j and q > digits1[i]) continue;
                    if (!k and r > digits2[i]) continue;
                    if (!l and n > q) continue;
                    if (!m and o > r) continue;

                    dp[i + 1][j or q < digits1[i]][k or r < digits2[i]]
                      [l or n < q][m or o < r] += dp[i][j][k][l][m];
                  }
                }
              }
            }
          }
        }
      }
    }

    mint ans = (mint) (A + 1) * (B + 1);
    ans += (mint) (A + 1) * (B + 1) * B / 2 * (mint(2).pow(M) - 2);
    ans += (mint) (B + 1) * (A + 1) * A / 2 * (mint(2).pow(N) - 2);
    ans += dp[K][1][1][1][1] * (mint(2).pow(N) - 2) * (mint(2).pow(M) - 2);
    cout << ans.val() << '\n';
  }
}