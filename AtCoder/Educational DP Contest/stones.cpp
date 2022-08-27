#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 100;
const I K = 1e5;

I dp[K + 1][2];
I a_arr[N];
I n;

I slv(I siz, I who) {
  if (dp[siz][who] != -1)
    return dp[siz][who];
  for (I i = 0; i < n; i++)
    if (siz - a_arr[i] >= 0 && slv(siz - a_arr[i], !who) == who)
      return dp[siz][who] = who;
  return dp[siz][who] = !who;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(I), -1);
  I k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  if (slv(k, 0) == 0)
    printf("First\n");
  else
    printf("Second\n");
  return 0;
}