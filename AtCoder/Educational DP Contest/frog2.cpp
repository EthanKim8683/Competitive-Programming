#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;
const I MAX = 1e9;

I h_arr[N];
I dp[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  fill_n(dp, n, MAX);
  for (I i = 0; i < n; i++)
    cin >> h_arr[i];
  dp[0] = 0;
  for (I i = 0; i < n; i++)
    for (I j = 1; j <= k && i + j < n; j++)
      dp[i + j] = min(dp[i + j], dp[i] + abs(h_arr[i] - h_arr[i + j]));
  printf("%i\n", dp[n - 1]);
  return 0;
}