#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

Lli MOD = 1e9 + 7;

I main(void) {
#ifdef ETHANKIM8683
  freopen("party.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  Lli res = 1;
  for (I i = 1; i <= n; i++)
    res = (res * i + (i % 2 ? -1 : 1)) % MOD;
  printf("%lli\n", res);
  return 0;
}