#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;

I dp[N][2];
pair<I, I> tres[N];

void cmb(I& a, I b) {
  a = max(a, b);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x, h;
    cin >> x >> h;
    tres[i] = {x, h};
  }
  sort(tres, tres + n);
  dp[0][1] = 1;
  for (I i = 0; i < n - 1; i++) {
    const auto [cur_x, cur_h] = tres[i];
    const auto [nex_x, nex_h] = tres[i + 1];
    if (cur_x + cur_h < nex_x)
      cmb(dp[i + 1][0], dp[i][0] + 1);
    if (cur_x + cur_h < nex_x - nex_h)
      cmb(dp[i + 1][1], dp[i][0] + 2);
    if (cur_x < nex_x)
      cmb(dp[i + 1][0], max(dp[i][0], dp[i][1]) + 0);
    if (cur_x < nex_x - nex_h)
      cmb(dp[i + 1][1], max(dp[i][0], dp[i][1]) + 1);
  }
  printf("%i\n", max(dp[n - 1][0] + 1, dp[n - 1][1]));
  return 0;
}