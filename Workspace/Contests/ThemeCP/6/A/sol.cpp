#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> C(2 * N);
  for (auto &e : C) cin >> e;

  vector dp(2 * N + 1, vector(N + 1, vector<int>(2, -1)));
  dp[0][0][0] = -2;
  int pm = -1;
  for (int i = 0; i < 2 * N; i++) {
    for (int j = 0; j <= N; j++) {
      for (int k = 0; k < 2; k++) {
        if (dp[i][j][k] == -1) continue;
        int j_ = j + (k == 0);
        if (j_ <= N) {
          dp[i + 1][j_][k] = k;
        }

        if (C[i] > pm) {
          int j_ = j + (1 - k == 0);
          if (j_ <= N) {
            dp[i + 1][j_][1 - k] = k;
          }
        }
      }
    }
    pm = max(pm, C[i]);
  }

  int i = 2 * N, j = N, k;
  for (k = 0; k < 2; k++) {
    if (dp[i][j][k] != -1) break;
  }
  if (k == 2) {
    cout << -1 << '\n';
    exit(0);
  }

  vector<int> ans[2];
  while (i > 0) {
    int k_ = dp[i][j][k];
    ans[k].push_back(C[i - 1]);

    i--;
    j -= k == 0;
    k = k_;
  }

  for (auto r : ans) {
    reverse(r.begin(), r.end());
    for (auto e : r) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
