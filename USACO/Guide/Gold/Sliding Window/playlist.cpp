#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;

vector<I> vals;
I k_arr[N];
B incs[N];

I cps(I val) {
  return upper_bound(vals.begin(), vals.end(), val) - vals.begin() - 1;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("playlist.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I k;
    cin >> k;
    k_arr[i] = k;
    vals.push_back(k);
  }
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  I l = 0;
  I r = 0;
  I res = 0;
  while (r < n) {
    if (incs[cps(k_arr[r])])
      incs[cps(k_arr[l++])] = false;
    else
      incs[cps(k_arr[r++])] = true;
    res = max(res, r - l);
  }
  printf("%i\n", res);
  return 0;
}