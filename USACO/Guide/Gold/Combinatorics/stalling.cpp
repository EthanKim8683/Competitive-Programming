#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 20;

I a_arr[N];
I b_arr[N];
Lli dp[1 << N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++)
    cin >> b_arr[i];
  dp[0] = 1;
  for (I i = 0; i < n; i++)
    for (I j = (1 << n) - 1; j >= 0; j--)
      if (__builtin_popcount(j) == i)
        for (I k = 0; k < n; k++)
          if (~j & (1 << k) && a_arr[i] <= b_arr[k])
            dp[j | (1 << k)] += dp[j];
  printf("%lli\n", dp[(1 << n) - 1]);
  return 0;
}