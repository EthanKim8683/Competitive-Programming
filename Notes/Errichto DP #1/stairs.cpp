#include <iostream>

using namespace std;

const int N = 1e5;

int dp[N + 1];

int main(void) {
  int n;
  cin >> n;
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    if (i + 1 <= n)
      dp[i + 1] += dp[i];
    if (i + 2 <= n)
      dp[i + 2] += dp[i];
  }
  cout << dp[n] << endl;
  return 0;
}