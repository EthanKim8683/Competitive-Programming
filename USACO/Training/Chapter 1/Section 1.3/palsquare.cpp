/*
ID: ethanki1
TASK: palsquare
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

I main(void) {
#ifndef ETHANKIM8683
  freopen("palsquare.in", "r", stdin);
  freopen("palsquare.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I b;
  cin >> b;
  for (I i = 1; i <= N; i++) {
    const S sqr = tob(i * i, b);
    if (pal(sqr))
      printf("%s %s\n", tob(i, b).c_str(), sqr.c_str());
  }
  return 0;
}