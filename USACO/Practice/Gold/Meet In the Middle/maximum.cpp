#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 35;

I lows[N / 2];
I upps[N - N / 2];
vector<Lli> low_vals;
vector<Lli> upp_vals;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  const I low = n / 2;
  const I upp = n - n / 2;
  for (I i = 0; i < low; i++)
    cin >> lows[i];
  for (I i = 0; i < upp; i++)
    cin >> upps[i];
  for (I i = 0; i < (1 << low); i++) {
    Lli sum = 0;
    for (I j = 0; j < low; j++)
      if (i >> j & 1)
        sum += lows[j];
    low_vals.push_back(sum % m);
  }
  for (I i = 0; i < (1 << upp); i++) {
    Lli sum = 0;
    for (I j = 0; j < upp; j++)
      if (i >> j & 1)
        sum += upps[j];
    upp_vals.push_back(sum % m);
  }
  sort(low_vals.begin(), low_vals.end());
  sort(upp_vals.begin(), upp_vals.end());
  low_vals.erase(unique(low_vals.begin(), low_vals.end()), low_vals.end());
  upp_vals.erase(unique(upp_vals.begin(), upp_vals.end()), upp_vals.end());
  Lli res = 0;
  for (const auto val : low_vals) {
    const auto it = upper_bound(upp_vals.begin(), upp_vals.end(), m - val - 1);
    if (it != upp_vals.begin())
      res = max(res, (val + upp_vals[it - upp_vals.begin() - 1]) % m);
  }
  printf("%lli\n", res);
  return 0;
}