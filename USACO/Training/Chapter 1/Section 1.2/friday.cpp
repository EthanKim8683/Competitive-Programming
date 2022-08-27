/*
ID: ethanki1
TASK: friday
LANG: C++14
*/

#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

const I L = 7;

I lens[12] = {
  31, 28, 31, 30,
  31, 30, 31, 31,
  30, 31, 30, 31
};
I days[L];

B lea(I yea) {
  return yea % 4 == 0 && (yea % 100 != 0 || yea % 400 == 0);
}

I len(I mon, I yea) {
  I res = lens[mon];
  if (mon == 1 && lea(yea))
    res++;
  return res;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("friday.in", "r", stdin);
  freopen("friday.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  I day = 0;
  for (I i = 1900; i <= 1900 + n - 1; i++) {
    for (I j = 0; j < 12; j++) {
      days[day]++;
      (day += len(j, i)) %= L;
    }
  }
  printf("%i", days[0]);
  for (I i = 1; i < L; i++)
    printf(" %i", days[i]);
  printf("\n");
  return 0;
}