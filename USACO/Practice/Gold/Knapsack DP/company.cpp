#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 100;
const I X = 5000;

I t_arr[N];
vector<pair<I, vector<pair<I, I>>>> dp[N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("company.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> t_arr[i];
  dp[0][0][0] = {t_arr[0], t_arr[0]};
  for (I i = 0; i < n; i++) {
    printf("%i: %i\n", i, dp[i]);
    for (I j = i; j < n; j++) {
      if (t_arr[j] - t_arr[i] > x)
        break;
      dp[j + 1] += dp[i];
    }
  }
  printf("%i\n", dp[n]);
  return 0;
}