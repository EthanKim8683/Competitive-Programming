#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

vector<I> vals;
I x_arr[N];
I cnts[N];
I cnt = 0;

I cps(I i) {
  return upper_bound(vals.begin(), vals.end(), i) - vals.begin() - 1;
}

void add(I i) {
  if (cnts[i]++ == 0)
    cnt++;
}

void rmv(I i) {
  if (--cnts[i] == 0)
    cnt--;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("distinct.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++) {
    I x;
    cin >> x;
    x_arr[i] = x;
    vals.push_back(x);
  }
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  I l = 0;
  I r = 0;
  Lli res = 0;
  while (r <= n) {
    if (cnt > k)
      rmv(cps(x_arr[l++]));
    else {
      res += r - l;
      if (r >= n)
        break;
      add(cps(x_arr[r++]));
    }
  }
  printf("%lli\n", res);
  return 0;
}