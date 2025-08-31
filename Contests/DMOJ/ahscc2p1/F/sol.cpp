#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<string> S(N);
  for (auto &e : S) cin >> e;

  vector<int> counts(N);
  for (int i = 0; i < N; i++) {
    counts[i] = count(S[i].begin(), S[i].end(), '1');
  }

  vector dp(N + 1, vector<bool>(M + 1, false));
  dp[0][0] = true;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= M; j++) {
      if (!dp[i][j]) continue;
      dp[i + 1][j] = true;
      // j' + counts[i]-(j-j')
      // j + counts[i]-(j-j') <= M
      // j' <= M-counts[i]
      // j-j' <= counts[i]
      // j' >= j-counts[i]
      for (int k = max(0, j - counts[i]); k <= min(M - counts[i], j); k++) {
        dp[i + 1][k + counts[i] - (j - k)] = true;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= M; i++) {
    if (dp[N][i]) {
      ans = i;
    }
  }
  cout << string(ans, '1') + string(M - ans, '0');
}
