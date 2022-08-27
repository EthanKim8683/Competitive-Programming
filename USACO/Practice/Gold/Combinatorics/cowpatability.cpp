#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I C = 5;
const I D = 1e6;
const Lli MOD = 119218851371;

I tmp[C];
unordered_map<Lli, Lli> cnts[2];

I main(void) {
#ifndef ETHANKIM8683
  freopen("cowpatibility.in", "r", stdin);
  freopen("cowpatibility.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < C; j++)
      cin >> tmp[j];
    sort(tmp, tmp + C);
    for (I j = 1; j < (1 << C); j++) {
      Lli key = 0;
      for (I k = 0; k < C; k++)
        if (j >> k & 1)
          key = (key * D + tmp[k]) % MOD;
      cnts[__builtin_popcount(j) % 2][key]++;
    }
  }
  Lli res = (Lli) n * (n - 1) / 2;
  for (I i = 0; i < 2; i++)
    for (const auto [key, cnt] : cnts[i])
      res += cnt * (cnt - 1) / 2 * (i ? -1 : 1);
  printf("%lli\n", res);
  return 0;
}