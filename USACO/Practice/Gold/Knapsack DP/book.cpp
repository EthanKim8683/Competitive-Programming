#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;

U hs[1000];
U ss[1000];
U dp[100001];
U js[100001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("book.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, x;
  cin >> n >> x;
  for (U i = 0; i < n; i++)
    cin >> hs[i];
  for (U i = 0; i < n; i++)
    cin >> ss[i];
  U result = 0;
  for (U i = 1; i <= x; i++) {
    U i_dp = 0;
    U i_js = 0;
    for (U j = 0; j < n; j++) {
      const I k = i - hs[j];
      if (k >= 0 && j >= js[k]) {
        const U k_dp = dp[k] + ss[j];
        if (k_dp > i_dp) {
          i_dp = k_dp;
          i_js = j;
        }
      }
    }
    result = max(result, i_dp);
    dp[i] = i_dp;
    js[i] = i_js + 1;
  }
  printf("%u\n", result);
  return 0;
}