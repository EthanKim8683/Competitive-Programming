#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5;
const int M = 1e5;

int coins[M];
int dp[N + 1];

int main(void) {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
    cin >> coins[i];
  fill_n(dp, n + 1, 1e9);
  dp[0] = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (i + coins[j] <= n)
        dp[i + coins[j]] = min(dp[i + coins[j]], dp[i] + 1);
  cout << dp[n] << '\n';
  return 0;
}