#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 1000
#define X 100000

using namespace std;

using I = int;

I h_arr[N];
I s_arr[N];
I dp[X + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("book.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> h_arr[i];
  for (I i = 0; i < n; i++)
    cin >> s_arr[i];
  fill_n(dp, x + 1, -1);
  dp[0] = 0;
  for (I i = 0; i < n; i++) {
    const auto h = h_arr[i];
    const auto s = s_arr[i];
    for (I j = x; j--;)
      if (dp[j] != -1 && j + h <= x)
        dp[j + h] = max(dp[j + h], dp[j] + s);
  }
  I result = 0;
  for (I i = 0; i <= x; i++)
    result = max(result, dp[i]);
  printf("%i\n", result);
  return 0;
}