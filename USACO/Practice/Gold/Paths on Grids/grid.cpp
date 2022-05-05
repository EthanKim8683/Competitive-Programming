#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using C = char;

const I MOD = 1e9 + 7;
const I N = 1000;

C grid[N][N];
Lli dp[N][N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("grid.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> grid[i];
  if (grid[0][0] == '*' || grid[n - 1][n - 1] == '*')
    printf("0\n");
  else {
    dp[0][0] = 1;
    for (I i = 0; i < n; i++) {
      for (I j = 0; j < n; j++) {
        if (grid[i][j] == '.') {
          if (i + 1 < n) {
            auto& a = dp[i + 1][j];
            a = (a + dp[i][j]) % MOD;
          }
          if (j + 1 < n) {
            auto& a = dp[i][j + 1];
            a = (a + dp[i][j]) % MOD;
          }
        }
      }
    }
    printf("%lli\n", dp[n - 1][n - 1]);
  }
  return 0;
}