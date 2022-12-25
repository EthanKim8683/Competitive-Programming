#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

// minimum:
// two pointers for the final n-wide range of consecutive cows

// maximum:
// width - min endpoint distance - count

const I N = 1e5;
const I MAX = 1e9;

I cows[N];
I n;

I che(I l, I r) {
  const I wid = cows[r] - cows[l] + 1;
  const I cnt = r - l + 1;
  I lef = l;
  I rig = n - r - 1;
  I gap = wid - cnt;
  if (lef == 1 && gap >= 1) {
    lef--;
    gap--;
  }
  if (rig == 1 && gap >= 1) {
    rig--;
    gap--;
  }
  if (lef >= 2) {
    gap -= min(lef, gap);
    lef = 0;
  }
  if (rig >= 2) {
    gap -= min(rig, gap);
    rig = 0;
  }
  if (lef > 0 || rig > 0 || gap > 0)
    return MAX;
  return n - cnt;
}

I sol1() {
  I l = 0;
  I r = 0;
  I res = che(l, r);
  while (l < r || r < n - 1) {
    const I wid = cows[r] - cows[l] + 1;
    if (r == n - 1)
      l++;
    else if (l == r)
      r++;
    else if (wid > n)
      l++;
    else if (wid <= n)
      r++;
    if (cows[r] - cows[l] + 1 <= n)
      res = min(res, che(l, r));
  }
  return res;
}

I sol2() {
  const I wid = cows[n - 1] - cows[0] + 1;
  const I lef = cows[1] - cows[0] - 1;
  const I rig = cows[n - 1] - cows[n - 2] - 1;
  return wid - min(lef, rig) - n;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("herding.in", "r", stdin);
  freopen("herding.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> cows[i];
  sort(cows, cows + n);
  printf("%i\n%i\n", sol1(), sol2());
  return 0;
}