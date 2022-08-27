#include <iostream>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

I f_arr[N];
pair<I, I> boos[N];
map<I, I> gaps;
set<I> blks;
I inds[N - 2];

B cmp(I a, I b) {
  return f_arr[a] > f_arr[b];
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("snowboots.in", "r", stdin);
  freopen("snowboots.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, b;
  cin >> n >> b;
  for (I i = 0; i < n; i++)
    cin >> f_arr[i];
  for (I i = 0; i < b; i++) {
    I s, d;
    cin >> s >> d;
    boos[i] = {s, d};
  }
  for (I i = 0; i < n; i++)
    blks.insert(i);
  iota(inds, inds + n - 2, 1);
  sort(inds, inds + n - 2, cmp);
  I gap = 1;
  for (I i = 0; i < n - 2; i++) {
    const I j = inds[i];
    const I f = f_arr[j];
    if (gaps[f] == 0)
      gaps[f] = gap;
    blks.erase(j);
    auto it = blks.upper_bound(j);
    const I upp = *it--;
    const I low = *it;
    gap = max(gap, upp - low);
  }
  if (gaps[0] == 0)
    gaps[0] = gap;
  for (I i = 0; i < b; i++) {
    const auto [s, d] = boos[i];
    printf("%i\n", (--gaps.upper_bound(s))->second <= d);
  }
  return 0;
}