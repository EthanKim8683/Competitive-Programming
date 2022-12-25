#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;
const I N = 100;
const I X = 5000;

I t_arr[N];
Lli dp[N + 1][N + 1][X + X + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("company.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = n; i--;)
    cin >> t_arr[i];
  sort(t_arr, t_arr + n);
  dp[0][0][X] = 1;
  for (I i = 0; i < n; i++) {
    const auto t = t_arr[i];
    for (I j = 0; j <= i; j++) {
      for (I k = 0; k <= X + x; k++) {
        const auto cur = dp[i][j][k];
        // open a group
        if (j + 1 <= n && k - t >= 0) {
          auto& nxt = dp[i + 1][j + 1][k - t];
          nxt = (nxt + cur) % MOD;
        }
        // close any group
        if (j - 1 >= 0 && k + t <= X + x) {
          auto& nxt = dp[i + 1][j - 1][k + t];
          nxt = (nxt + j * cur) % MOD;
        }
        auto& nxt = dp[i + 1][j][k];
        // add to any group
        nxt = (nxt + j * cur) % MOD;
        // open and close a group of one
        nxt = (nxt + cur) % MOD;
      }
    }
  }
  Lli res = 0;
  for (I i = X; i <= X + x; i++)
    res = (res + dp[n][0][i]) % MOD;
  printf("%lli\n", res);
  return 0;
}