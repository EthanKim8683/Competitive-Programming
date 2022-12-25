#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;

const I N = 1e5;

pair<I, I> pais[N];
vector<I> dp;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x1, x2;
    cin >> x1 >> x2;
    pais[i] = {x1, x2};
  }
  sort(pais, pais + n, greater<pair<I, I>>());
  for (I i = 0; i < n; i++) {
    const auto [x1, x2] = pais[i];
    const auto it = upper_bound(dp.begin(), dp.end(), x2);
    if (it == dp.end())
      dp.push_back(x2);
    else
      *it = x2;
  }
  printf("%i\n", dp.size());
  return 0;
}