#include <iostream>
#include <cstdio>

#define N 100000

using namespace std;

using I = int;
using Lli = long long int;

Lli hist[N + 1];
Lli dp[N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("455a.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = n; i--;) {
    I a;
    cin >> a;
    hist[a]++;
  }
  dp[0] = 0;
  dp[1] = hist[1];
  for (Lli i = 2; i <= N; i++)
    dp[i] = max(dp[i - 1], dp[i - 2] + i * hist[i]);
  printf("%lli\n", dp[N]);
  return 0;
}