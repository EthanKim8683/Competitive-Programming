/*
ID: ethanki1
TASK: barn1
LANG: C++14
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I S = 200;

B occs[S];
vector<I> blks;

I main(void) {
#ifndef ETHANKIM8683
  freopen("barn1.in", "r", stdin);
  freopen("barn1.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I m, s, c;
  cin >> m >> s >> c;
  for (I i = 0; i < c; i++) {
    I cow;
    cin >> cow;
    occs[cow - 1] = true;
  }
  I cnt = 0;
  I beg = 0;
  while (beg < s) {
    I end = beg + 1;
    while (end < s && occs[beg] == occs[end])
      end++;
    if (occs[beg])
      cnt++;
    else if (beg != 0 && end != s)
      blks.push_back(end - beg);
    beg = end;
  }
  sort(blks.begin(), blks.end());
  I res = c;
  for (I i = 0; i < cnt - m; i++)
    res += blks[i];
  printf("%i\n", res);
  return 0;
}