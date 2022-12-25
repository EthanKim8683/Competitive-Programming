#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;

pair<I, I> cows[N];
pair<I, Lli> rngs[N];
vector<Lli> dp;

I main(void) {
#ifndef ETHANKIM8683
  freopen("cowjog.in", "r", stdin);
  freopen("cowjog.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, t;
  cin >> n >> t;
  for (I i = 0; i < n; i++)
    cin >> cows[i].first >> cows[i].second;
  for (I i = 0; i < n; i++) {
    const auto [pos, spd] = cows[i];
    rngs[i] = {pos, pos + (Lli) spd * t};
  }
  sort(rngs, rngs + n, greater<pair<I, Lli>>());
  for (I i = 0; i < n; i++) {
    const auto [beg, end] = rngs[i];
    const auto it = upper_bound(dp.begin(), dp.end(), end);
    if (it == dp.end())
      dp.push_back(end);
    else
      *it = end;
  }
  printf("%i\n", dp.size());
  return 0;
}