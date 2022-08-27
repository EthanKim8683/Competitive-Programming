#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 50000;

B uses[2 * N + 1];
I lows[N / 2];
I upps[N / 2];
vector<I> bess;

I main(void) {
#ifndef ETHANKIM8683
  freopen("cardgame.in", "r", stdin);
  freopen("cardgame.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n / 2; i++)
    cin >> upps[i];
  for (I i = 0; i < n / 2; i++)
    cin >> lows[i];
  for (I i = 0; i < n / 2; i++) {
    uses[upps[i]] = true;
    uses[lows[i]] = true;
  }
  for (I i = 1; i <= 2 * n; i++)
    if (!uses[i])
      bess.push_back(i);
  sort(upps, upps + n / 2, greater<I>());
  sort(lows, lows + n / 2);
  I res = 0;
  sort(bess.begin(), bess.end());
  for (I i = 0; i < n / 2; i++) {
    const I upp = upps[i];
    if (bess.back() > upp) {
      bess.pop_back();
      res++;
    }
  }
  reverse(bess.begin(), bess.end());
  for (I i = 0; i < n / 2; i++) {
    const I low = lows[i];
    if (bess.back() < low) {
      bess.pop_back();
      res++;
    }
  }
  printf("%i\n", res);
  return 0;
}