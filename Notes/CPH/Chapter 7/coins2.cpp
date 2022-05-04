#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5;
const int M = 1e5;

int c_arr[M];
int dp[N + 1];

int main(void) {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
    cin >> c_arr[i];
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      const int k = i + c_arr[j];
      if (k <= n)
        dp[k] += dp[i];
    }
  }
  cout << dp[n] << '\n';
  return 0;
}