#include <iostream>
#include <cstdio>
#include <algorithm>
#include <numeric>

using namespace std;

using I = int;

const I N = 3e5;

I prm[N];
I res[N];
I tmp[N];
I n;

void rif(I seq[], I prm[]) {
  for (I i = 0; i < n; i++)
    tmp[i] = seq[prm[i]];
  copy_n(tmp, n, seq);
}

void pow(I prm[], I pow) {
  iota(res, res + n, 1);
  while (pow) {
    if (pow & 1)
      rif(res, prm);
    rif(prm, prm);
    pow >>= 1;
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I k;
    cin >> n >> k;
    I cur = 0;
    for (I i = 0; i < n - 2; i++, cur += 2)
      prm[i] = cur;
    cur = 1;
    for (I i = n / 2; i < n; i++, cur += 2)
      prm[i] = cur;
    pow(prm, k);
    printf("%i", res[0]);
    for (I i = 1; i < n; i++)
      printf(" %i", res[i]);
    printf("\n");
  }
  return 0;
}