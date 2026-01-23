#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  int Cs, Cw, Cd;
  cin >> Cs >> Cw >> Cd;

  int Ps, Pw, Pd;
  cin >> Ps >> Pw >> Pd;

  vector<string> A(2);
  for (auto &e : A) cin >> e;

  // how many swordsmen to use (maximize wizards), how many wizards to use
  // (maximize swordsmen)

  int M = 0;
  for (auto r : A) {
    for (auto e : r) {
      M += e == '.';
    }
  }

  auto chmax = [&](int &a, int b) -> void { a = max(a, b); };

  vector dp(N + 1, vector(Cs + 1, vector(9, -INF)));
  dp[0][0][0] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= Cs; j++) {
      vector grid(2, vector<int>(2, 0));
      for (int k = 0; k < 9; k++) {
        grid[0][0] = k / 3;
        grid[0][1] = k % 3;
        if (i - 1 >= 0) {
          if (A[0][i - 1] == '#' and grid[0][0] != 0) continue;
          if (A[1][i - 1] == '#' and grid[0][1] != 0) continue;
        }
        for (int l = 0; l < 9; l++) {
          grid[1][0] = l / 3;
          grid[1][1] = l % 3;
          if (A[0][i] == '#' and grid[1][0] != 0) continue;
          if (A[1][i] == '#' and grid[1][1] != 0) continue;
          if ((grid[0][0] == 1 and grid[0][1] == 1) or
              (grid[1][0] == 1 and grid[1][1] == 1) or
              (grid[0][0] == 1 and grid[1][0] == 1) or
              (grid[0][1] == 1 and grid[1][1] == 1))
            continue;
          if ((grid[0][0] == 2 and grid[1][1] == 2) or
              (grid[1][0] == 2 and grid[0][1] == 2))
            continue;
          int j_ = j + (grid[1][0] == 1) + (grid[1][1] == 1);
          if (j_ <= Cs) {
            chmax(dp[i + 1][j_][l],
                  dp[i][j][k] + (grid[1][0] == 2) + (grid[1][1] == 2));
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= Cs; i++) {
    for (int j = 0; j < 9; j++) {
      int k = min(dp[N][i][j], Cw);
      if (k < 0) continue;

      int l = min(M - i - k, Cd);
      chmax(ans, i * Ps + k * Pw + l * Pd);

      int l_ = min(M - i, Cd), k_ = min(min(dp[N][i][j], M - i - l_), Cw);
      chmax(ans, i * Ps + k_ * Pw + l_ * Pd);
    }
  }
  cout << ans;
}