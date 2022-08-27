#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;
using S = string;
using Lli = long long int;

const I B = 5000;
const I N = 1000;
const Lli MOD = 1e9 + 7;

set<I> inds[10];
Lli dp[B][N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  S b;
  cin >> b;
  I n;
  cin >> n;
  for (I i = 0; i < b.size(); i++)
    inds[b[i] - '0'].insert(i);
  for (I i = 1; i < 10; i++)
    if (!inds[i].empty())
      dp[*inds[i].begin()][0] = 1;
  Lli res = 0;
  for (I i = 0; i < b.size(); i++) {
    const I dgt = b[i] - '0';
    inds[dgt].erase(inds[dgt].begin());
    for (I j = 0; j < n; j++) {
      if (dp[i][j] > 0) {
        for (I k = 0; k < 10; k++)
          if (!inds[k].empty())
            (dp[*inds[k].begin()][(j * 10 + dgt) % n] += dp[i][j]) %= MOD;
        if ((j * 10 + dgt) % n == 0)
          (res += dp[i][j]) %= MOD;
      }
    }
  }
  printf("%lli\n", res);
  return 0;
}