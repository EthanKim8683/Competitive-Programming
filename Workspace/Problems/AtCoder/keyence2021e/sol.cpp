#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  auto chmax = [&](int &a, int b) -> void { a = max(a, b); };
  vector dp(N + 1, vector(N + 1, vector<int>(N + 2, -INF)));
  for (int i = 0; i <= N + 1; i++) {
    dp[0][N][i] = 0;
  }
  for (int i = N; i > 0; i--) {
    for (int j = 0; j + i <= N; j++) {
      for (int k = 0; k <= N + 1; k++) {
        if (k - 1 >= 0) {
          if (j + i >= N or A[j] > A[j + i]) {
            chmax(dp[j + 1][j + i][k - 1], dp[j][j + i][k]);
          }
          if (j - 1 < 0 or A[j + i - 1] > A[j - 1]) {
            chmax(dp[j][j + i - 1][k - 1], dp[j][j + i][k]);
          }
        }
        if (k + 1 <= N + 1) {
          chmax(dp[j + 1][j + i][k + 1], dp[j][j + i][k] + A[j]);
          chmax(dp[j][j + i - 1][k + 1], dp[j][j + i][k] + A[j + i - 1]);
        }
      }
    }
  }
  for (int i = 0; i <= N; i++) {
    cout << dp[i][i][1] << '\n';
  }

  // for (int i = 0; i <= N; i++) {
  //   auto chmax = [&](int &a, int b) -> void { a = max(a, b); };
  //   vector dp(N + 1, vector(N + 1, vector<int>(N + 1, -INF)));
  //   dp[i][i][1] = 0;
  //   for (int j = 0; j < N; j++) {
  //     for (int k = 0; k + j <= N; k++) {
  //       for (int l = 0; l <= j + 1; l++) {
  //         if (k - 1 >= 0 and (k + j == N or A[k - 1] > A[k + j])) {
  //           chmax(dp[k - 1][k + j][l + 1], dp[k][k + j][l]);
  //         } else {
  //           chmax(dp[k][k + j + 1][l + 1], dp[k][k + j][l]);
  //         }
  //         if (l >= 0) {
  //           if (k - 1 >= 0) {
  //             chmax(dp[k - 1][k + j][l - 1], dp[k][k + j][l] + A[k - 1]);
  //           }
  //           if (k + j < N) {
  //             chmax(dp[k][k + j + 1][l - 1], dp[k][k + j][l] + A[k + j]);
  //           }
  //         }
  //       }
  //     }
  //   }
  //   cout << *max_element(dp[0][N].begin(), dp[0][N].end()) << '\n';
  // }
}
