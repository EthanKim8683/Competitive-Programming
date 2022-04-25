#include <iostream>
#include <cstdio>

#define N 100
#define X 1000
#define M (N * X)

using namespace std;

using I = int;
using B = bool;

I x_arr[N];
B dp[M + 1];
I ress[M];

I main(void) {
#ifdef ETHANKIM8683
  freopen("sums.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  dp[0] = true;
  for (I i = 0; i < n; i++) {
    const auto x = x_arr[i];
    for (I j = M; j--;)
      if (dp[j] && j + x <= M)
        dp[j + x] = true;
  }
  I tot = 0;
  for (I i = 1; i <= M; i++)
    if (dp[i])
      ress[tot++] = i;
  printf("%i\n", tot);
  for (I i = 0; i < tot; i++)
    printf("%i ", ress[i]);
  return 0;
}