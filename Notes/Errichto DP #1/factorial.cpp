#include <iostream>

using namespace std;

const int N = 1e5;

long long int dp[N + 1];

int main(void) {
  int n;
  cin >> n;
  dp[0] = 1;
  for (int i = 1; i <= n; i++)
    dp[i] = dp[i - 1] * i;
  cout << dp[n] << '\n';
  return 0;
}