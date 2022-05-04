#include <iostream>

using namespace std;

const int N = 1e5;

long long int dp[N];

int main(void) {
  int n;
  cin >> n;
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i < n; i++)
    dp[i] = dp[i - 1] + dp[i - 2];
  cout << dp[n - 1] << '\n';
}