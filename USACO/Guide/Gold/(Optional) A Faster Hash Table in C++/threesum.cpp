#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 5000;
const I A = 1e6;

I a_arr[N];
I cnts[A + A + 1];
Lli dp[N + 1][N + 1];

I main(void) {
#ifndef ETHANKIM8683
  freopen("threesum.in", "r", stdin);
  freopen("threesum.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++) {
    const I a = a_arr[i];
    for (I j = n - 1; j > i; j--)
      cnts[a_arr[j] + A]++;
    for (I j = n - 1; j > i; j--) {
      const I b = a_arr[j];
      const I c = 0 - a - b;
      cnts[b + A]--;
      if (c >= -A && c <= A)
        dp[i][j] = cnts[c + A];
    }
  }
	for (int i = n - 1; i >= 0; i--)
    for (int j = i + 1; j < n; j++)
		  dp[i][j] += dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
  while (q--) {
    I a, b;
    cin >> a >> b;
    printf("%lli\n", dp[a - 1][b - 1]);
  }
  return 0;
}