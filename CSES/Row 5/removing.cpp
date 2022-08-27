// start 9:20
// end 9:21
// tries 1

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e6;
const I MAX = 1e9;

I dp[N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(dp, n + 1, MAX);
  dp[n] = 0;
  for (I i = n; i >= 0; i--)
    if (dp[i] != MAX)
      for (I tmp = i; tmp; tmp /= 10)
        dp[i - tmp % 10] = min(dp[i - tmp % 10], dp[i] + 1);
  printf("%i\n", dp[0]);
  return 0;
}