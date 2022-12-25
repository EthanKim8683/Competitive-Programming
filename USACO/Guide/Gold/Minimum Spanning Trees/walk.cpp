#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 7500;
const Lli X = 2019201913;
const Lli Y = 2019201949;
const Lli MOD = 2019201997;

I edgs[N];

I main(void) {
  freopen("walk.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("walk.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 1; i + 1 <= n; i++) {
    I min_y = -1;
    I min_dst = MOD;
    for (I j = i + 1; j <= n; j++) {
      const I dst = (X * i + Y * j) % MOD;
      if (dst < min_dst) {
        min_y = j;
        min_dst = dst;
      }
    }
    edgs[i - 1] = min_dst;
  }
  k = n - k;
  nth_element(edgs, edgs + k, edgs + n - 1);
  printf("%i\n", edgs[k]);
  return 0;
}