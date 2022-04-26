#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 100;

C s[N + 1];
vector<C> dp[N + 1][8];

I main(void) {
#ifdef ETHANKIM8683
  freopen("550c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  I n = 0;
  while (s[n]) {
    const auto c = s[n];
    for (I j = 8; j--;) {
      if (!dp[n][j].empty() || j == 0) {
        const I k = (j * 10 + c - '0') % 8;
        dp[n + 1][k] = dp[n][j];
        dp[n + 1][k].emplace_back(c);
      }
      if (!dp[n][j].empty())
        dp[n + 1][j] = dp[n][j];
    }
    n++;
  }
  if (dp[n][0].empty())
    printf("NO\n");
  else {
    printf("YES\n");
    for (const auto c : dp[n][0])
      printf("%c", c);
  }
  return 0;
}