#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;
const int MAXK = 200;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // int N = 1e5;

  // vector<int> dp(N + 1, INF);
  // dp[0] = 0;
  // for (int i = 0; i <= N; i++) {
  // 	for (int v = 1; i + v <= N; v = v * 4 + 1) {
  // 		dp[i + v] = min(dp[i + v], dp[i] + 1);
  // 	}
  // }

  // for (int i = 0; i <= N; i++) {
  // 	vector<int> zebra;
  // 	for (int v = 1; v <= i; v = v * 4 + 1) {
  // 		zebra.push_back(v);
  // 	}
  // 	reverse(zebra.begin(), zebra.end());

  // 	int v = i, greedy = 0;
  // 	for (auto e : zebra) {
  // 		while (v - e >= 0) {
  // 			v -= e;
  // 			greedy++;
  // 		}
  // 	}
  // 	assert(dp[i] == greedy);
  // }

  int T;
  cin >> T;

  while (T--) {
    i64 L, R, K;
    cin >> L >> R >> K;

    auto solve = [&](i64 x) -> i64 {
      if (K > MAXK) return 0;

      vector<i64> zebra;
      for (i64 v = 1; v <= x; v = 4 * v + 1) {
        zebra.push_back(v);
      }
      reverse(zebra.begin(), zebra.end());

      i64 v = x;
      vector<int> digits;
      for (auto e : zebra) {
        int digit = 0;
        while (v - e >= 0) {
          v -= e;
          digit++;
        }
        digits.push_back(digit);
      }

      vector dp(digits.size() + 1, vector(K + 1, vector(2, vector<i64>(2, 0))));
      dp[0][0][0][0] = 1;
      for (int i = 0; i < digits.size(); i++) {
        for (int j = 0; j <= K; j++) {
          for (int k = 0; k <= 4; k++) {
            for (int l = 0; l < 2; l++) {
              for (int m = 0; m < 2; m++) {
                if (j + k > K) continue;
                if (l and k > 0) continue;
                if (!m and k > digits[i]) continue;

                dp[i + 1][j + k][l or k == 4][m or k < digits[i]] +=
                    dp[i][j][l][m];
              }
            }
          }
        }
      }
      i64 rv = 0;
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          rv += dp[digits.size()][K][i][j];
        }
      }
      return rv;
    };
    cout << solve(R) - solve(L - 1) << '\n';
  }
}