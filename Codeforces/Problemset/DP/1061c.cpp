#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100000;
const I A = 1e6;
const Lli MOD = 1e9 + 7;

I a_arr[N];
Lli dp[A + 1];
Lli chgs[A + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  dp[0] = 1;
  for (I i = 1; i <= n; i++) {
    I a;
    cin >> a;
    for (I j = 1; j * j <= a; j++) {
      if (a % j == 0) {
        chgs[j] = dp[j - 1];
        const I k = a / j;
        if (k != j)
          chgs[k] = dp[k - 1];
      }
    }
    for (I j = 1; j * j <= a; j++) {
      if (a % j == 0) {
        dp[j] = (dp[j] + chgs[j]) % MOD;
        chgs[j] = 0;
        const I k = a / j;
        if (k != j) {
          dp[k] = (dp[k] + chgs[k]) % MOD;
          chgs[k] = 0;
        }
      }
    }
  }
  Lli res = 0;
  for (I i = 1; i <= n; i++)
    res = (res + dp[i]) % MOD;
  printf("%lli\n", res);
  return 0;
}