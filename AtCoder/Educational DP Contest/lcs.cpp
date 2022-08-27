#include <iostream>
#include <cstdio>
 
using namespace std;
 
using I = int;
using S = string;
 
const I L = 3000;
 
pair<I, I> dp[L + 1][L + 1];
 
I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  S s;
  cin >> s;
  S t;
  cin >> t;
  const I s_len = s.size();
  const I t_len = t.size();
  for (I i = 0; i <= s_len; i++) {
    for (I j = 0; j <= t_len; j++) {
      if (i < s_len && j < t_len && s[i] == t[j] && dp[i][j].first + 1 > dp[i + 1][j + 1].first)
        dp[i + 1][j + 1] = {dp[i][j].first + 1, 1};
      if (i < s_len && dp[i][j].first > dp[i + 1][j].first)
        dp[i + 1][j] = {dp[i][j].first, 2};
      if (j < t_len && dp[i][j].first > dp[i][j + 1].first)
        dp[i][j + 1] = {dp[i][j].first, 3};
    }
  }
  I i = s_len;
  I j = t_len;
  S res = "";
  while (true) {
    const auto [cnt, dir] = dp[i][j];
    if (cnt == 0)
      break;
    if (dir == 1) {
      i--;
      j--;
      res = s[i] + res;
    } else if (dir == 2)
      i--;
    else if (dir == 3)
      j--;
  }
  printf("%s\n", res.c_str());
  return 0;
}