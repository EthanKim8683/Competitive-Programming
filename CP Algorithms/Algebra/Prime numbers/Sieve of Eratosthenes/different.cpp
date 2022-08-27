#include <iostream>
#include <cstdio>
#include <algorithm>
#include <numeric>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 2000000;

I facs[N + 1];
I inds[N + 1];

B cmp(I a, I b) {
  if (facs[a] == facs[b])
    return a < b;
  return facs[a] < facs[b];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  for (I i = 2; i <= N; i++) {
    if (facs[i] == 0) {
      Lli val = i;
      while (val <= N) {
        for (I j = val; j <= N; j += val)
          facs[j]++;
        val *= i;
      }
    }
  }
  iota(inds, inds + N + 1, 0);
  sort(inds, inds + N + 1, cmp);
  I i = 1;
  while (true) {
    I n;
    cin >> n;
    if (n == 0)
      break;
    printf("Case %i: %i\n", i++, inds[n]);
  }
  return 0;
}