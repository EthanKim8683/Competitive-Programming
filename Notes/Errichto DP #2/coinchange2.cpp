#include <iostream>

using namespace std;

const int N = 1e3;
const int M = 1e3;

int coins[M];
int dp[N + 1][M];

int main(void) {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
    cin >> coins[i];
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i + coins[j] <= n)
        dp[i + coins[j]][j] += dp[i][j];
      if (j + 1 < m)
        dp[i][j + 1] += dp[i][j];
    }
  }
  int res = 0;
  for (int i = 0; i < m; i++)
    res += dp[n][i];
  cout << res << '\n';
  return 0;
}