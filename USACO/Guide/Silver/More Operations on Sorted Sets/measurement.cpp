#include <iostream>
#include <cstdio>
#include <tuple>
#include <algorithm>
#include <map>

using namespace std;

using I = int;

const I N = 100000;
const I MAX = 1e9;

tuple<I, I, I> upds[N];
map<I, pair<I, I>> prds;
map<I, I> cows;

I main(void) {
#ifndef ETHANKIM8683
  freopen("measurement.in", "r", stdin);
  freopen("measurement.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, g;
  cin >> n >> g;
  for (I i = 0; i < n; i++) {
    I day, cow, upd;
    cin >> day >> cow >> upd;
    upds[i] = {day, cow, upd};
  }
  sort(upds, upds + n);
  prds.insert({g, {-1, MAX}});
  I res = 0;
  pair<I, I> lst_dat = {-1, -1};
  for (I i = 0; i < n; i++) {
    const auto [day, cow, upd] = upds[i];
    if (cows[cow] == 0)
      cows[cow] = g;
    if (--prds[cows[cow]].second == 0)
      prds.erase(cows[cow]);
    cows[cow] += upd;
    prds[cows[cow]].second++;
    prds[cows[cow]].first = cow;
    const auto [prd, dat] = *--prds.end();
    if (dat != lst_dat)
      res++;
    lst_dat = dat;
  }
  printf("%i\n", res);
  return 0;
}