#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 50000;
const Lli MAX = 1e18;
const Lli MIN = -1e18;

pair<Lli, Lli> cows[N];
Lli lft_sizs[N];
Lli rgt_sizs[N];

B cmp(pair<Lli, Lli> a, pair<Lli, Lli> b) {
  return a.second < b.second;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("split.in", "r", stdin);
  freopen("split.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  Lli x_low = MAX;
  Lli x_upp = MIN;
  Lli y_low = MAX;
  Lli y_upp = MIN;
  for (I i = 0; i < n; i++) {
    Lli x, y;
    cin >> x >> y;
    x_low = min(x_low, x);
    x_upp = max(x_upp, x);
    y_low = min(y_low, y);
    y_upp = max(y_upp, y);
    cows[i] = {x, y};
  }
  const Lli tot = (x_upp - x_low) * (y_upp - y_low);
  Lli res = MAX;
  sort(cows, cows + n);
  Lli low = MAX;
  Lli upp = MIN;
  for (I i = n - 1; i >= 0; i--) {
    rgt_sizs[i] = upp - low;
    low = min(low, cows[i].second);
    upp = max(upp, cows[i].second);
  }
  low = MAX;
  upp = MIN;
  for (I i = 0; i < n; i++) {
    low = min(low, cows[i].second);
    upp = max(upp, cows[i].second);
    lft_sizs[i] = upp - low;
  }
  Lli lft_beg = cows[0].first;
  Lli rgt_end = cows[n - 1].first;
  for (I i = 0; i < n - 1; i++) {
    const Lli lft_end = cows[i].first;
    const Lli rgt_beg = cows[i + 1].first;
    const Lli lft_tot = lft_sizs[i] * (lft_end - lft_beg);
    const Lli rgt_tot = rgt_sizs[i] * (rgt_end - rgt_beg);
    res = min(res, lft_tot + rgt_tot);
  }
  sort(cows, cows + n, cmp);
  low = MAX;
  upp = MIN;
  for (I i = n - 1; i >= 0; i--) {
    rgt_sizs[i] = upp - low;
    low = min(low, cows[i].first);
    upp = max(upp, cows[i].first);
  }
  low = MAX;
  upp = MIN;
  for (I i = 0; i < n; i++) {
    low = min(low, cows[i].first);
    upp = max(upp, cows[i].first);
    lft_sizs[i] = upp - low;
  }
  lft_beg = cows[0].second;
  rgt_end = cows[n - 1].second;
  for (I i = 0; i < n - 1; i++) {
    const Lli lft_end = cows[i].second;
    const Lli rgt_beg = cows[i + 1].second;
    const Lli lft_tot = lft_sizs[i] * (lft_end - lft_beg);
    const Lli rgt_tot = rgt_sizs[i] * (rgt_end - rgt_beg);
    res = min(res, lft_tot + rgt_tot);
  }
  printf("%lli\n", tot - res);
  return 0;
}