#include <iostream>

using namespace std;

const int N = 1e5;
const int M = 1e5;

int nums[M];
int dp[N + 1];

int main(void) {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
    cin >> nums[i];
  dp[0] = 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (i + nums[j] <= n)
        dp[i + nums[j]] += dp[i];
  cout << dp[n] << '\n';
  return 0;
}