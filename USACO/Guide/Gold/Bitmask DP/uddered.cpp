#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using S = string;
using B = bool;
using Lli = long long int;

const I N = 20;
const Lli MAX = 1e18;

B viss[26];
I inds[26];
I invs[26][26];
Lli dp[1 << N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  S str;
  cin >> str;
  for (const auto chr : str)
    viss[chr - 'a'] = true;
  I cnt = 0;
  for (I i = 0; i < 26; i++)
    if (viss[i])
      inds[i] = cnt++;
  for (I i = 0; i + 1 < str.size(); i++)
    invs[inds[str[i] - 'a']][inds[str[i + 1] - 'a']]++;
  fill_n(dp, 1 << cnt, MAX);
  dp[0] = 1;
  for (I i = 0; i < (1 << cnt); i++) {
    for (I j = 0; j < cnt; j++) {
      if (~i >> j & 1) {
        Lli tot = dp[i] + invs[j][j];
        for (I k = 0; k < cnt; k++)
          if (i >> k & 1)
            tot += invs[j][k];
        dp[i | 1 << j] = min(dp[i | 1 << j], tot);
      }
    }
  }
  printf("%lli\n", dp[(1 << cnt) - 1]);
  return 0;
}