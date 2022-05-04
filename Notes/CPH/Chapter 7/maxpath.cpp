#include <iostream>

using namespace std;

const int N = 1e3;

int grid[N][N];
int dp[N][N];

int main(void) {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> grid[i][j];
  dp[0][0] = grid[0][0];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i + 1 < n)
        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + grid[i + 1][j]);
      if (j + 1 < n)
        dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + grid[i][j + 1]);
    }
  }
  cout << dp[n - 1][n - 1] << '\n';
  return 0;
}