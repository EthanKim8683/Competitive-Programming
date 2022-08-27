#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 1e4;

B coms[N + 1];
Lli dp[N + 1];

I main(void) {
#ifndef ETHANKIM8683
  freopen("exercise.in", "r", stdin);
  freopen("exercise.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  dp[0] = 1;
  for (I i = 2; i <= n; i++) {
    if (!coms[i]) {
      for (I j = i * i; j <= n; j += i)
        coms[j] = true;
      for (I j = n; j >= 0; j--)
        for (I k = i; k + j <= n; k *= i)
          (dp[j + k] += dp[j] * k) %= m;
    }
  }
  Lli res = 0;
  for (I i = 0; i <= n; i++)
    (res += dp[i]) %= m;
  printf("%lli\n", res);
  return 0;
}