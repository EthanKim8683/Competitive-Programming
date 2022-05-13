#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;

const int N = 2e5;

I x_arr[N];
vector<I> dp;

I main(void) {
#ifdef ETHANKIM8683
  freopen("increasing.in", "r", stdin);
#endif
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x;
    cin >> x;
    const auto j = lower_bound(dp.begin(), dp.end(), x) - dp.begin();
    if (j == dp.size())
      dp.push_back(x);
    else
      dp[j] = x;
  }
  printf("%i\n", dp.size());
  return 0;
}