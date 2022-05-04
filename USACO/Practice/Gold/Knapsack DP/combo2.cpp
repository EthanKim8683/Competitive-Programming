#include <iostream>
#include <cstdio>
#include <algorithm>
 
using namespace std;

using I = int;

const I MOD = 1e9 + 7;
const I N = 100;
const I X = 1e6;

I c_arr[N];
I dp[X + 1];
 
int main(void) {
#ifdef ETHANKIM8683
  freopen("combo2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> c_arr[i];
  dp[0] = 1;
  for (I i = 0; i < n; i++) {
    const auto c = c_arr[i];
    for (I j = 0; j < x; j++) {
      const auto k = j + c;
      if (k <= x)
        dp[k] = (dp[k] + dp[j]) % MOD;
    }
  }
  printf("%i\n", dp[x]);
  return 0;
}