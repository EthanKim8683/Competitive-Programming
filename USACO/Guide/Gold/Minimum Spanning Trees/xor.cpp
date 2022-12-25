#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 200000;
const I BITS = 30;
const I MAX = 1 << BITS;

I nods[N * BITS][2];
I mins[N * BITS];
I a_arr[N];
I cnt = 0;

I qry(I cur, I dep, I val) {
  I res = 0;
  if (dep < BITS) {
    I msk = 1 << (BITS - 1 - dep);
    for (I i = dep; i < BITS; i++) {
      const B bit = val & msk;
      if (nods[cur][bit] == 0) {
        cur = nods[cur][!bit];
        res |= msk;
      } else
        cur = nods[cur][bit];
      msk >>= 1;
    }
  }
  return res;
}

void add(I val) {
  I msk = 1 << (BITS - 1);
  I cur = 0;
  for (I i = 0; i < BITS; i++) {
    const B bit = val & msk;
    if (nods[cur][!bit] != 0)
      mins[cur] = min(mins[cur], msk | qry(nods[cur][!bit], i + 1, val));
    if (nods[cur][bit] == 0)
      cur = nods[cur][bit] = ++cnt;
    else
      cur = nods[cur][bit];
    msk >>= 1;
  }
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("xor.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(mins, n * BITS, MAX);
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  sort(a_arr, a_arr + n);
  for (I i = 0; i < n; i++)
    add(a_arr[i]);
  Lli res = 0;
  for (I i = 0; i < cnt; i++)
    if (mins[i] != MAX)
      res += mins[i];
  printf("%lli\n", res);
  return 0;
}