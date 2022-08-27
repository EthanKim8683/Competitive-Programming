#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 1e6;
const I M = 1e3;

I a_arr[N];
B dp[M + 1][M];
B viss[M];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  if (n > m) {
    Lli acc = 0;
    viss[acc] = true;
    for (I i = 0; i < n; i++) {
      (acc += a_arr[i]) %= m;
      if (viss[acc]) {
        printf("YES\n");
        return 0;
      }
      viss[acc] = true;
    }
    printf("NO\n");
  } else {
    for (I i = 0; i < n; i++) {
      const I a = a_arr[i];
      dp[i + 1][a % m] = true;
      for (I j = 0; j < m; j++) {
        dp[i + 1][(j + a) % m] |= dp[i][j];
        dp[i + 1][j] |= dp[i][j];
      }
    }
    if (dp[n][0])
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}