#include <iostream>

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
  dp[0] = 1;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (j + coins[i] <= n)
        dp[j + coins[i]] += dp[i];
  cout << dp[n] << '\n';
  return 0;
}