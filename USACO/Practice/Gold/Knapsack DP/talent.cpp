#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 250;
const I W = 1000;

pair<I, I> c_arr[N];
I dp[W];

I rat(I wgt, I tal) {
  if (wgt == 0)
    return 0;
  return tal * 1000 / wgt;
}

I main(void) {
  freopen("talent.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("talent.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, w;
  cin >> n >> w;
  for (I i = 0; i < n; i++) {
    I w, t;
    cin >> w >> t;
    c_arr[i] = {w, t};
  }
  sort(c_arr, c_arr + n);
  I res_w = 0;
  I res_t = 0;
  I res_rat = 0;
  fill_n(dp, w, -1);
  dp[0] = 0;
  for (I i = 0; i < n; i++) {
    const auto [wgt, tal] = c_arr[i];
    if (res_w != 0 && rat(wgt, tal) > res_rat) {
      res_w += wgt;
      res_t += tal;
      res_rat = rat(res_w, res_t);
    }
    for (I j = w - 1; j >= 0; j--) {
      if (dp[j] != -1) {
        const I nxt_w = j + wgt;
        const I nxt_t = dp[j] + tal;
        if (nxt_w >= w) {
          if (rat(nxt_w, nxt_t) > res_rat) {
            res_w = nxt_w;
            res_t = nxt_t;
            res_rat = rat(res_w, res_t);
          }
        } else
          dp[nxt_w] = max(dp[nxt_w], nxt_t);
      }
    }
  }
  printf("%i\n", rat(res_w, res_t));
  return 0;
}