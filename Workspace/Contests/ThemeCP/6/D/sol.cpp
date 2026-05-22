#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  int C = N * 300;
  vector dp(N + 1, vector<int>(C + N * 300 + 1, -2));
  dp[0][C + 0] = -1;
  for (int i = 0; i < N; i++) {
    for (int j = -i * 300; j <= i * 300; j++) {
      if (dp[i][C + j] == -2) continue;
      dp[i + 1][C + j - A[i]] = -1;
      dp[i + 1][C + j + A[i]] = 1;
    }
  }
  if (dp[N][C + 0] == -2) {
    cout << "First" << endl;
    while (true) {
      int j;
      for (j = 0; j < N; j++) {
        if (A[j] > 0) break;
      }
      cout << j + 1 << endl;

      int i;
      cin >> i;
      if (i == -1 or i == 0) exit(0);
      i--;

      int d = min(A[i], A[j]);
      A[i] -= d;
      A[j] -= d;
    }
  } else {
    vector<int> signs(N);
    int i = N, j = C + 0;
    while (i != 0) {
      int s = dp[i][j];
      signs[i - 1] = s;
      j -= s * A[i - 1];
      i--;
    }

    cout << "Second" << endl;
    while (true) {
      int i;
      cin >> i;
      if (i == -1 or i == 0) exit(0);
      i--;

      int j = 0;
      for (j = 0; j < N; j++) {
        if (j != i and signs[j] == -signs[i]) break;
      }
      cout << j + 1 << endl;

      if (A[i] <= A[j]) {
        signs[i] = 0;
      }
      if (A[i] >= A[j]) {
        signs[j] = 0;
      }
      int d = min(A[i], A[j]);
      A[i] -= d;
      A[j] -= d;
    }
  }
}
