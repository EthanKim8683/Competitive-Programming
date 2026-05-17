#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // fix min and max

  int N;
  cin >> N;

  vector R(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      cin >> R[i][j];
      R[j][i] = R[i][j];
    }
  }

  vector<int> ans(N);
  auto solve = [&](auto self, int l, int r, int i, bool is_min) -> void {
    if (r - l <= 1) return;
    tuple<int, int, int> best = {-1, -1, -1};
    for (int j = l; j < r; j++) {
      if (j == i) continue;
      best = max(best, {R[i][j], -abs(i - j), j});
    }
    auto [d, n, j] = best;
    if (is_min) {
      ans[j] = ans[i] + d;
    } else {
      ans[j] = ans[i] - d;
    }
    if (i == l) {
      self(self, l, j, i, is_min);
      self(self, j, r, j, !is_min);
    } else {
      self(self, j + 1, r, i, is_min);
      self(self, l, j + 1, j, !is_min);
    }
  };
  tuple<int, int, int> best = {-1, -1, -1};
  for (int l = 0; l < N; l++) {
    for (int r = l; r < N; r++) {
      best = max(best, {R[l][r], -abs(r - l), l});
    }
  }
  auto [d, n, i] = best;
  solve(solve, i, N, i, true);
  solve(solve, 0, i + 1, i, true);
  for (int i = 0; i < N; i++) {
    cout << ans[i] << " \n"[i == N - 1];
  }
}
