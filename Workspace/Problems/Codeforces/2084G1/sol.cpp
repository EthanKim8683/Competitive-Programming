#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    // f(c) = {
    //   max(c[l], c[r])  if l % 2 == r % 2
    //   min(c[l], c[r])  if l % 2 != r % 2
    // }

    vector<vector<int>> included(2);
    for (int i = 0; i < N; i++) {
      if (A[i] == 0) continue;
      included[i % 2].push_back(A[i]);
    }

    vector<bool> seen(N + 1, false);
    for (auto e : A) {
      if (e == 0) continue;
      seen[e] = true;
    }

    vector<int> excluded;
    for (int i = 1; i <= N; i++) {
      if (seen[i]) continue;
      excluded.push_back(i);
    }

    vector<int> count(2);
    for (int i = 0; i < N; i++) {
      if (A[i] != 0) continue;
      count[i % 2]++;
    }

    vector count_ps(2, vector<int>(N + 1 + 1, 0));
    vector sum_ps(2, vector<i64>(N + 1 + 1, 0));
    for (int i = 0; i < 2; i++) {
      for (auto e : included[i]) {
        count_ps[i][e + 1]++;
        sum_ps[i][e + 1] += e;
      }

      for (int j = 1; j <= N; j++) {
        count_ps[i][j + 1] += count_ps[i][j];
        sum_ps[i][j + 1] += sum_ps[i][j];
      }
    }

    auto chmax = [&](i64 &a, i64 b) -> void { a = max(a, b); };

    vector dp(excluded.size() + 1, vector<i64>(count[0] + 1, -INF));
    dp[0][0] = 0;
    for (int i = 0; i < excluded.size(); i++) {
      int v = excluded[i];
      for (int j = 0; j <= min(i, count[0]); j++) {
        int k = i - j;

        if (j + 1 <= count[0]) {
          i64 sum = dp[i][j];
          sum += (i64) v * (j + 1);
          sum += (i64) v * count_ps[0][v];
          sum += sum_ps[0][N + 1] - sum_ps[0][v];
          sum += (i64) v * (count[1] - k);
          sum += (i64) v * (count_ps[1][N + 1] - count_ps[1][v]);
          sum += sum_ps[1][v];
          chmax(dp[i + 1][j + 1], sum);
        }

        if (k + 1 <= count[1]) {
          i64 sum = dp[i][j];
          sum += (i64) v * (k + 1);
          sum += (i64) v * count_ps[1][v];
          sum += sum_ps[1][N + 1] - sum_ps[1][v];
          sum += (i64) v * (count[0] - j);
          sum += (i64) v * (count_ps[0][N + 1] - count_ps[0][v]);
          sum += sum_ps[0][v];
          chmax(dp[i + 1][j], sum);
        }
      }
    }
    i64 ans = dp[excluded.size()][count[0]];

    for (int i = 0; i < N; i++) {
      for (int j = i; j < N; j++) {
        if (A[i] == 0 or A[j] == 0) continue;

        if (i % 2 == j % 2) {
          ans += max(A[i], A[j]);
        } else {
          ans += min(A[i], A[j]);
        }
      }
    }

    cout << ans << '\n';
  }
}