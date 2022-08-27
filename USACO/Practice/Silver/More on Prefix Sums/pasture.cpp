#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2500;

pair<I, I> cows[N];
Lli ps[N + 1][N + 1];
I vals1[N];
I vals2[N];
I n;

I cps1(I x) {
  return find(vals1, vals1 + n, x) - vals1;
}

I cps2(I x) {
  return find(vals2, vals2 + n, x) - vals2;
}

Lli rng(I x1, I y1, I x2, I y2) {
  return ps[x2][y2] - ps[x1][y2] - ps[x2][y1] + ps[x1][y1];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> cows[i].first >> cows[i].second;
  for (I i = 0; i < n; i++) {
    const auto [x, y] = cows[i];
    vals1[i] = x;
    vals2[i] = y;
  }
  sort(vals1, vals1 + n);
  sort(vals2, vals2 + n);
  for (I i = 0; i < n; i++) {
    const auto [x, y] = cows[i];
    cows[i] = {cps1(x), cps2(y)};
  }
  for (I i = 0; i < n; i++) {
    const auto [x, y] = cows[i];
    ps[x + 1][y + 1] = 1;
  }
  for (I i = 1; i <= n; i++)
    for (I j = 1; j <= n; j++)
      ps[i][j] += ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
  Lli res = 1 + n;
  for (I i = 0; i < n; i++) {
    const auto [x1, y1] = cows[i];
    for (I j = 0; j < n; j++) {
      const auto [x2, y2] = cows[j];
      if (x1 < x2)
        res += rng(x1, 0, x2 + 1, min(y1, y2) + 1) * rng(x1, max(y1, y2), x2 + 1, n);
    }
  }
  printf("%lli\n", res);
  return 0;
}