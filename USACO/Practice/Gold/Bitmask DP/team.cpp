#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const Lli MIN = -1e18;
const I MAX = 1e9;
const I N = 1e5;
const I P = 7;

pair<Lli, I> dp[1 << P];
I plys[1 << P][P];
I a_arr[N];
I s_arr[N][P];
I inds[N];

B cmp(I a, I b) {
  return a_arr[a] > a_arr[b];
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("team.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, p, k;
  cin >> n >> p >> k;
  fill_n(dp, 1 << p, pair<Lli, I>{MIN, 0});
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++)
    for (I j = 0; j < p; j++)
      cin >> s_arr[i][j];
  for (I i = 0; i < n; i++)
    inds[i] = i;
  sort(inds, inds + n, cmp);
  dp[0] = {0, 0};
  for (I i = 0; i < n; i++) {
    for (I j = (1 << p) - 1; j >= 0; j--) {
      for (I k = 0; k < p; k++)
        if (~j & (1 << k) && dp[j].first + s_arr[inds[i]][k] > dp[j | (1 << k)].first)
          dp[j | (1 << k)] = {dp[j].first + s_arr[inds[i]][k], dp[j].second};
      if (dp[j].second < k) {
        dp[j].first += a_arr[inds[i]];
        dp[j].second++;
      }
    }
  }
  printf("%lli\n", dp[(1 << p) - 1].first);
  return 0;
}