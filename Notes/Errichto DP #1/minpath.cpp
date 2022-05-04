#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e3;
const int M = 1e3;

int grid[N][M];
int dp[N][M];

int main(void) {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> grid[i][j];
  for (int i = 0; i < n; i++)
    fill_n(dp[i], m, 1e9);
  dp[0][0] = grid[0][0];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i + 1 < n)
        dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + grid[i + 1][j]);
      if (j + 1 < m)
        dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + grid[i][j + 1]);
    }
  }
  cout << dp[n - 1][m - 1] << '\n';
  return 0;
}