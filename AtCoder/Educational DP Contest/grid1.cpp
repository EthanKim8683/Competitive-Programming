#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using C = char;
using Lli = long long int;

const I H = 1000;
const I W = 1000;
const Lli MOD = 1e9 + 7;

C cels[H][W];
Lli dp[H][W];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I h, w;
  cin >> h >> w;
  for (I i = 0; i < h; i++)
    cin >> cels[i];
  if (cels[0][0] != '#')
    dp[0][0] = 1;
  for (I i = 0; i < h; i++) {
    for (I j = 0; j < w; j++) {
      if (i + 1 < h && cels[i + 1][j] != '#')
        (dp[i + 1][j] += dp[i][j]) %= MOD;
      if (j + 1 < w && cels[i][j + 1] != '#')
        (dp[i][j + 1] += dp[i][j]) %= MOD;
    }
  }
  printf("%lli\n", dp[h - 1][w - 1]);
  return 0;
}