#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;

pair<I, I> frds[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, d;
  cin >> n >> d;
  for (I i = 0; i < n; i++) {
    I m, s;
    cin >> m >> s;
    frds[i] = {m, s};
  }
  sort(frds, frds + n);
  I l = 0;
  I r = 0;
  Lli sum = frds[l].second;
  Lli res = 0;
  while (l < r || r < n - 1) {
    const I dif = frds[r].first - frds[l].first;
    if (dif < d)
      res = max(res, sum);
    if (r == n - 1)
      sum -= frds[l++].second;
    else if (l == r)
      sum += frds[++r].second;
    else if (dif >= d)
      sum -= frds[l++].second;
    else if (dif < d)
      sum += frds[++r].second;
  }
  const I dif = frds[r].first - frds[l].first;
  if (dif < d)
    res = max(res, sum);
  printf("%lli\n", res);
  return 0;
}