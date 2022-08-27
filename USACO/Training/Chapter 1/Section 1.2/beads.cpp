/*
ID: ethanki1
TASK: beads
LANG: C++14
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>

using namespace std;

using I = int;
using C = char;

const I N = 350;

C beas[2 * N];
deque<pair<C, I>> unqs;

void add(C col) {
  if (col == 'w')
    return;
  if (unqs.empty() || col != unqs.back().first)
    unqs.push_back({col, 1});
  else
    unqs.back().second++;
}

void rem(C col) {
  if (col == 'w')
    return;
  if (--unqs.front().second == 0)
    unqs.pop_front();
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("beads.in", "r", stdin);
  freopen("beads.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  cin >> beas;
  copy_n(beas, n, beas + n);
  I l = 0;
  I r = 0;
  add(beas[l]);
  I res = 1;
  while (l < r || r < 2 * n - 1) {
    if (r == 2 * n - 1)
      rem(beas[l++]);
    else if (l == r)
      add(beas[++r]);
    else if (unqs.size() > 2)
      rem(beas[l++]);
    else if (unqs.size() <= 2)
      add(beas[++r]);
    if (unqs.size() <= 2)
      res = max(res, r - l + 1);
  }
  printf("%i\n", min(res, n));
  return 0;
}