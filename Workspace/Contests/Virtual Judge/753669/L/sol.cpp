#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<string> A(N);
  for (auto &e : A) cin >> e;

  // max(dx, dy)

  vector sum_ps(N, vector<int>(M + 1, 0)), count_ps(N, vector<int>(M + 1, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      sum_ps[i][j + 1] += sum_ps[i][j];
      count_ps[i][j + 1] += count_ps[i][j];
      if (A[i][j] == '1') {
        sum_ps[i][j + 1] += j;
        count_ps[i][j + 1] += 1;
      }
    }
  }

  vector count_ps_(N + 1, vector<int>(M + 1, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      count_ps_[i + 1][j + 1] = A[i][j] == '1';
    }
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      count_ps_[i][j] +=
          count_ps_[i][j - 1] + count_ps_[i - 1][j] - count_ps_[i - 1][j - 1];
    }
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int R, C, K;
    cin >> R >> C >> K;
    R--, C--;

    int x = 0;
    for (; x <= max(N, M); x++) {
      int r1 = max(R - x, 0), r2 = min(R + x + 1, N);
      int c1 = max(C - x, 0), c2 = min(C + x + 1, M);
      if (count_ps_[r2][c2] - count_ps_[r1][c2] - count_ps_[r2][c1] +
              count_ps_[r1][c1] >=
          K) {
        x--;
        break;
      }
    }

    auto solve = [&](int x) -> pair<int, int> {
      int sum = 0, count = 0;
      for (int i = max(R - x, 0); i <= min(R + x, N - 1); i++) {
        int dr = abs(i - R);
        int l1 = max(C - x, 0), l2 = max(C - dr, 0);
        int r1 = min(C + dr + 1, M), r2 = min(C + x + 1, M);
        sum += (count_ps[i][r1] - count_ps[i][l2]) * dr;
        sum += C * (count_ps[i][l2] - count_ps[i][l1]) -
               (sum_ps[i][l2] - sum_ps[i][l1]);
        sum += (sum_ps[i][r2] - sum_ps[i][r1]) -
               C * (count_ps[i][r2] - count_ps[i][r1]);
        count += count_ps[i][r2] - count_ps[i][l1];
      }
      return {sum, count};
    };
    auto [ans, count] = solve(x);
    ans += (x + 1) * (K - count);
    ans *= 2;
    cout << ans << '\n';
  }
}