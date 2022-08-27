#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2000;

Lli dp[N + 1];
I a_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(dp, n + 1, -1);
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  dp[0] = 0;
  for (I i = 0; i < n; i++) {
    const I a = a_arr[i];
    for (I j = i; j >= 0; j--)
      if (dp[j] != -1 && dp[j] + a >= 0)
        dp[j + 1] = max(dp[j + 1], dp[j] + a);
  }
  for (I i = n; i >= 0; i--) {
    if (dp[i] != -1) {
      printf("%i\n", i);
      break;
    }
  }
  return 0;
}