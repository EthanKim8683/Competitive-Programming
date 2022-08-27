#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 50000;

I sizs[N];
I rgts[N];
I lfts[N];

I main(void) {
#ifndef ETHANKIM8683
  freopen("diamond.in", "r", stdin);
  freopen("diamond.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> sizs[i];
  sort(sizs, sizs + n);
  I l = 0;
  I r = 0;
  const I cnt = r - l + 1;
  rgts[r] = max(rgts[r], cnt);
  lfts[l] = max(lfts[l], cnt);
  while (l < r || r < n - 1) {
    const I dif = sizs[r] - sizs[l];
    if (r == n - 1)
      l++;
    else if (l == r)
      r++;
    else if (dif > k)
      l++;
    else if (dif <= k)
      r++;
    if (sizs[r] - sizs[l] <= k) {
      const I cnt = r - l + 1;
      rgts[r] = max(rgts[r], cnt);
      lfts[l] = max(lfts[l], cnt);
    }
  }
  for (I i = 0; i + 1 < n; i++)
    rgts[i + 1] = max(rgts[i + 1], rgts[i]);
  for (I i = n - 1; i - 1 >= 0; i--)
    lfts[i - 1] = max(lfts[i - 1], lfts[i]);
  I res = 0;
  for (I i = 0; i + 1 < n; i++)
    res = max(res, rgts[i] + lfts[i + 1]);
  printf("%i\n", res);
  return 0;
}