#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector dp(
      2, vector(3, vector(3, vector(2, vector(3, vector(3, vector<char>(
                                                               2, false)))))));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 2; k++) {
        dp[0][i][j][k][i][j][k] = true;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 2; l++) {
          for (int m = 0; m < 3; m++) {
            for (int n = 0; n < 3; n++) {
              for (int o = 0; o < 2; o++) {
                for (int p = 0; p < 3; p++) {
                  bool op = (m == 0 and n == 1 and p == 2) or
                            (m == 2 and n == 1 and p == 0);
                  if (A[i] == 1 or o or op) {
                    dp[(i + 1) % 2][j][k][l][n][p][op] |=
                        dp[i % 2][j][k][l][m][n][o];
                  }
                }
                dp[i % 2][j][k][l][m][n][o] = false;
              }
            }
          }
        }
      }
    }
  }
  char ans = false;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 2; k++) {
        ans |= dp[N % 2][i][j][k][i][j][k];
      }
    }
  }
  cout << (ans ? "Yes" : "No");
}
