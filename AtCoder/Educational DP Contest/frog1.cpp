#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;
const I MAX = 1e9;

I dp[N];
I h_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(dp, n, MAX);
  for (I i = 0; i < n; i++)
    cin >> h_arr[i];
  dp[0] = 0;
  for (I i = 0; i < n; i++) {
    if (i + 1 < n)
      dp[i + 1] = min(dp[i + 1], dp[i] + abs(h_arr[i] - h_arr[i + 1]));
    if (i + 2 < n)
      dp[i + 2] = min(dp[i + 2], dp[i] + abs(h_arr[i] - h_arr[i + 2]));
  }
  printf("%i\n", dp[n - 1]);
  return 0;
}