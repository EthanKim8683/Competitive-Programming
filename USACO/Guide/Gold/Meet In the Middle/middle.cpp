#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 40;

Lli lows[N / 2];
Lli upps[N / 2];
vector<Lli> low_vals;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  const I low = n / 2;
  const I upp = n - low;
  for (I i = 0; i < low; i++)
    cin >> lows[i];
  for (I i = 0; i < upp; i++)
    cin >> upps[i];
  for (I i = 0; i < (1 << low); i++) {
    Lli sum = 0;
    for (I j = 0; j < low && sum <= x; j++)
      if (i >> j & 1)
        sum += lows[j];
    if (sum <= x)
      low_vals.push_back(sum);
  }
  sort(low_vals.begin(), low_vals.end());
  Lli res = 0;
  for (I i = 0; i < (1 << upp); i++) {
    Lli sum = 0;
    for (I j = 0; j < upp && sum <= x; j++)
      if (i >> j & 1)
        sum += upps[j];
    if (sum <= x) {
      const Lli val = x - sum;
      const auto beg = lower_bound(low_vals.begin(), low_vals.end(), val);
      const auto end = upper_bound(low_vals.begin(), low_vals.end(), val);
      res += end - beg;
    }
  }
  printf("%lli\n", res);
  return 0;
}