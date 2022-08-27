/*
ID: ethanki1
TASK: crypt1
LANG: C++14
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 10;

I dgts[N];
I n;

B vld(I dgt) {
  return find(dgts, dgts + n, dgt) != dgts + n;
}

B chk(I val) {
  for (; val; val /= 10)
    if (!vld(val % 10))
      return false;
  return true;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("crypt1.in", "r", stdin);
  freopen("crypt1.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> dgts[i];
  sort(dgts, dgts + n);
  I res = 0;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < n; j++) {
      for (I k = 0; k < n; k++) {
        for (I l = 0; l < n; l++) {
          for (I m = 0; m < n; m++) {
            const I fac = dgts[i] + dgts[j] * 10 + dgts[k] * 100;
            const I apa = fac * dgts[l];
            const I bpa = fac * dgts[m];
            if (apa < 1000 && bpa < 1000 && chk(apa) && chk(bpa))
              res += chk(apa + bpa * 10);
          }
        }
      }
    }
  }
  printf("%i\n", res);
  return 0;
}