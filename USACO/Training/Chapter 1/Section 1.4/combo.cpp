/*
ID: ethanki1
TASK: combo
LANG: C++14
*/

#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

I n;
I f1, f2, f3;
I m1, m2, m3;

I dis(I i, I trg) {
  I res = abs(trg - i);
  res = min(res, abs(trg + n - i));
  res = min(res, abs(trg - n - i));
  return res;
}

B vld(I i, I trg) {
  return dis(i, trg) <= 2;
}

B chk(I i, I j, I k) {
  return (vld(i, f1) && vld(j, f2) && vld(k, f3)) ||
         (vld(i, m1) && vld(j, m2) && vld(k, m3));
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("combo.in", "r", stdin);
  freopen("combo.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  cin >> f1 >> f2 >> f3;
  cin >> m1 >> m2 >> m3;
  I res = 0;
  for (I i = 1; i <= n; i++)
    for (I j = 1; j <= n; j++)
      for (I k = 1; k <= n; k++)
        res += chk(i, j, k);
  printf("%i\n", res);
  return 0;
}