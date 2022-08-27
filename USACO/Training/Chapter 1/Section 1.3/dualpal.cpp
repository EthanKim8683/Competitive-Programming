/*
ID: ethanki1
TASK: dualpal
LANG: C++14
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using S = string;
using B = bool;
using C = char;

const I N = 300;

C toc(I i, I b) {
  I res = i % b;
  if (res >= 10)
    res += 'A' - 10;
  else
    res += '0';
  return res;
}

S tob(I i, I b) {
  if (i == 0)
    return "0";
  S res = "";
  for (; i; i /= b)
    res += toc(i, b);
  reverse(res.begin(), res.end());
  return res;
}

B pal(S str) {
  for (I l = 0, r = str.size() - 1; l < r; l++, r--)
    if (str[l] != str[r])
      return false;
  return true;
}

B chk(I val) {
  I cnt = 0;
  for (I i = 2; i <= 10; i++)
    cnt += pal(tob(val, i));
  return cnt >= 2;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("dualpal.in", "r", stdin);
  freopen("dualpal.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, s;
  cin >> n >> s;
  I cnt = 0;
  while (cnt < n) {
    s++;
    if (chk(s)) {
      printf("%i\n", s);
      cnt++;
    }
  }
  return 0;
}